#include "gxpch.h"
#include "Allocator.h"

namespace GinX
{
	size_t AlignmentHelper::__alignedSize(size_t s)
	{
		return ((s + __ALIGNMENT - 1) / __ALIGNMENT) * __ALIGNMENT;
	}

	bool AlignmentHelper::__isAligned(char* p)
	{
		return 0 == (reinterpret_cast<uintptr_t>(p) % __ALIGNMENT);
	}


	StandardAllocator* StandardAllocator::s_GlobalInstance = nullptr;

	void* StandardAllocator::AllocateMemory(size_t size)
	{
		return malloc(size);
	}

	void StandardAllocator::FreeMemory(void* mem, size_t size)
	{
		if (mem == nullptr)
			return;

		free(mem);
	}

	StandardAllocator& StandardAllocator::GlobalInstance()
	{
		if (s_GlobalInstance == nullptr)
		{
			static char allocatorInstanceMemory[sizeof(StandardAllocator)];
			StandardAllocator* stdAllocator = new(allocatorInstanceMemory) StandardAllocator();
			s_GlobalInstance = stdAllocator;
		}

		return (StandardAllocator&)(*s_GlobalInstance);
	}

}
