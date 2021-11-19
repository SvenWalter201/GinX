#include "gxpch.h"
#include "CustomAllocators.h"

namespace GinX
{
	/************************************************************

	//////////////////// Stack Allocator /////////////////////////

	*************************************************************/

	StackAllocator::StackAllocator(size_t stackSize, IAllocator* parentAllocator)
	{
		if (parentAllocator == nullptr)
			parentAllocator = &StandardAllocator::GlobalInstance();

		m_ParentAllocator = parentAllocator;

		m_StackSize = alignedSize(stackSize);

		m_StackBegin = (char*)m_ParentAllocator->AllocateMemory(m_StackSize);
		m_StackPtr = m_StackBegin;
	}

	StackAllocator::~StackAllocator()
	{
		if (m_ParentAllocator != nullptr)
		{
			m_ParentAllocator->FreeMemory(m_StackBegin, m_StackSize);
		}
	}

	void* StackAllocator::AllocateMemory(size_t size)
	{
		GX_ASSERT(size > 0, "Size must be bigger than zero");
		size = alignedSize(size);

		//check if the stack is still large enough
		if (m_StackPtr + size <= m_StackBegin + m_StackSize)
		{
			char* location = m_StackPtr;
			m_StackPtr += size;
			return location;
		}

		return nullptr;
	}

	void StackAllocator::FreeMemory(void* mem, size_t size)
	{
		if (mem == nullptr)
			return;

		size = alignedSize(size);
		m_StackPtr -= size;
	}

	void StackAllocator::FreeToMarker(void* mem)
	{
		if (mem == nullptr)
			return;

		m_StackPtr = (char*)mem;
	}

	void StackAllocator::Wipe()
	{
		m_StackPtr = m_StackBegin;
	}



	/************************************************************

	//////////////////// Pool Allocator /////////////////////////

	*************************************************************/


	PoolAllocator::PoolAllocator(size_t numChunks, size_t chunkSize, IAllocator* parentAllocator)
	{
		if (parentAllocator == nullptr)
			parentAllocator = &StandardAllocator::GlobalInstance();

		m_ParentAllocator = parentAllocator;

		GX_ASSERT(chunkSize > 0, "Chunksize must be bigger than zero");
		m_ChunkSize = alignedSize(chunkSize);

		GX_ASSERT(numChunks > 0, "Must allocate atleast one chunk");
		m_NumChunks = numChunks;

		m_PoolSize = m_ChunkSize * m_NumChunks;
		m_PoolBegin = (char*)m_ParentAllocator->AllocateMemory(m_PoolSize);
		
		m_IndexList = (int*)m_ParentAllocator->AllocateMemory(m_NumChunks * sizeof(int));
		
		for (size_t i = 0; i < m_NumChunks - 1; i++)
			m_IndexList[i] = (int)(i + 1);
		
		m_IndexList[numChunks - 1] = INVALID;
		m_NextFreeIndex = 0;
	}

	PoolAllocator::~PoolAllocator()
	{
		m_ParentAllocator->FreeMemory(m_PoolBegin, m_PoolSize);
		m_ParentAllocator->FreeMemory(m_IndexList, m_NumChunks * sizeof(int));
	}

	void* PoolAllocator::AllocateMemory(size_t size)
	{
		GX_ASSERT(size > 0, "Can't allocate 0 bytes");

		size = alignedSize(size);

		GX_ASSERT(size <= m_ChunkSize, "Cannot allocate bigger chunks than specified ChunkSize");
		
		if (m_NextFreeIndex == INVALID)
			return nullptr;

		int index = m_NextFreeIndex;
		char* location = m_PoolBegin + m_ChunkSize * index;
		m_NextFreeIndex = m_IndexList[index];
		m_IndexList[index] = INVALID;
		return location;
	}

	void PoolAllocator::FreeMemory(void* mem, size_t size)
	{
		if (mem == nullptr)
			return;

		int chunkIndex = (reinterpret_cast<char*>(mem) - m_PoolBegin) / m_ChunkSize;
		GX_ASSERT(m_IndexList[chunkIndex] == INVALID, "Can't free unused memory");

		m_IndexList[chunkIndex] = m_NextFreeIndex;
		m_NextFreeIndex = chunkIndex;
	}

}