#pragma once

namespace GinX
{
	class DynamicArray
	{
		typedef int* iterator;

	public:

		DynamicArray();
		DynamicArray(uint32_t initialCapacity);
		~DynamicArray();

		int& operator [](uint32_t index) {
			return m_Values[index];
		}

		int operator [](uint32_t index) const 
		{ 
			return m_Values[index];
		}
		

		void Resize(uint32_t newSize);
		void Reserve(uint32_t newCapacity);

		void Append(int element);
		void Append(int* elements, uint32_t count);

		void Insert(uint32_t index);
		void Delete(uint32_t index);

		//iterator begin();
		//iterator end();

		inline uint32_t Size() { return m_CurrentSize; }
		inline uint32_t Reserved() { return m_CurrentCapacity - m_CurrentSize; }
		inline int Get(uint32_t index) { return m_Values[index]; }

		void* operator new(size_t size) // regular new
		{
			return ::new char[sizeof(int)];
		}

		void* operator new(size_t size, void* pWhere) {
			return pWhere;
		}

	private:
		uint32_t m_CurrentCapacity = 0;
		uint32_t m_CurrentSize = 0;
		int* m_Values;
	};
}