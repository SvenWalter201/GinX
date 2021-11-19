#pragma once

namespace GinX
{
	/// <summary>
	/// Interface for custom Allocators
	/// </summary>
	class IAllocator
	{
	public:
		virtual void* AllocateMemory(size_t size) = 0;
		virtual void FreeMemory(void* mem, size_t size) = 0;
	};

	class StandardAllocator : public IAllocator
	{
	public:
		virtual void* AllocateMemory(size_t size) override;
		virtual void FreeMemory(void* mem, size_t size) override;

		static StandardAllocator& GlobalInstance();

		static StandardAllocator* s_GlobalInstance;

	private:
		StandardAllocator(){}
		~StandardAllocator(){}
	};

	struct AlignmentHelper
	{
		static const size_t __ALIGNMENT = sizeof(void*);
		static size_t __alignedSize(size_t s);
		static bool __isAligned(char* p);
	};



#define ALIGNMENT AlignmentHelper::__ALIGNMENT 
#define alignedSize AlignmentHelper::__alignedSize 
#define isAligned AlignmentHelper::__isAligned 
}