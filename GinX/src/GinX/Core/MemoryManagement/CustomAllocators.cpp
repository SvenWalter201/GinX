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


	PoolAllocator::PoolAllocator(size_t poolSize, size_t chunkSize)
	{

	}

	PoolAllocator::~PoolAllocator()
	{

	}

	void* PoolAllocator::AllocateMemory(size_t size)
	{
		return nullptr;
	}

	void PoolAllocator::FreeMemory(void* mem, size_t size)
	{

	}

}