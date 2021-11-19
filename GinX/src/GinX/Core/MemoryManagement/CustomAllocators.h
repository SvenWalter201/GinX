#pragma once

#include "Allocator.h"

namespace GinX
{
	/************************************************************
	
	//////////////////// Stack Allocator /////////////////////////

	*************************************************************/

	class StackAllocator : public IAllocator
	{
	public:
		StackAllocator(size_t stackSize, IAllocator* parentAllocator = nullptr);
		~StackAllocator();

		//IAllocator Methods
		virtual void* AllocateMemory(size_t size) override;
		virtual void FreeMemory(void* mem, size_t size) override;
		
		/// <summary>
		/// Get the current Size of the Stack
		/// </summary>
		/// <returns></returns>
		inline size_t GetCurrentStackSize() const { return m_StackPtr - m_StackBegin; }
		
		/// <summary>
		/// Get the size of the reserved memory for the Stack to use
		/// </summary>
		/// <returns></returns>
		inline size_t GetStackSize() const { return m_StackSize; }
		
		/// <summary>
		/// Get the current position in the stack to return to it later
		/// </summary>
		/// <returns></returns>
		inline void* GetMarker() { return m_StackPtr; }

		/// <summary>
		/// Reset the Stack to a certain location (Obtained with GetMarker())
		/// </summary>
		/// <param name="mem"> - The desired address to reset the stack to</param>
		void FreeToMarker(void* mem);

		/// <summary>
		/// Reset the entire Stack
		/// </summary>
		void Wipe();
	private:
		size_t m_StackSize;
		char* m_StackBegin;
		char* m_StackPtr;
		IAllocator* m_ParentAllocator;


		//not accessible
		StackAllocator() {}
		StackAllocator(const StackAllocator&) {}
		StackAllocator(StackAllocator&& other) {}
	};


	/************************************************************

	//////////////////// Pool Allocator /////////////////////////

	*************************************************************/

	class PoolAllocator : public IAllocator
	{
	public:
		PoolAllocator(size_t poolSize, size_t chunkSize);
		~PoolAllocator();

		virtual void* AllocateMemory(size_t size) override;
		virtual void FreeMemory(void* mem, size_t size) override;

	private:
		char* m_PoolBegin;
		size_t m_PoolSize;

		size_t m_ChunkSize;
		size_t m_NumChunks;

		int m_NextFreeIndex;

		IAllocator* m_ParentAllocator;

		//not accessible
		PoolAllocator() {}
		PoolAllocator(const PoolAllocator&) {}
		PoolAllocator(PoolAllocator&& other) {}
	};
}