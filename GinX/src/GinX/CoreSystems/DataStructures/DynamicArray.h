#pragma once

namespace GinX
{
	template<typename T>
	class DynamicArray
	{
		typedef int* iterator;

	public:

		DynamicArray()
			: m_CurrentSize(0), m_CurrentCapacity(0), m_Values(new T[0])
		{

		}
		DynamicArray(uint32_t initialCapacity)
			: m_CurrentSize(0), m_CurrentCapacity(initialCapacity), m_Values(new T[initialCapacity])
		{

		}

		~DynamicArray() {}

		T& operator [](uint32_t index) {
			return m_Values[index];
		}

		T operator [](uint32_t index) const 
		{ 
			return m_Values[index];
		}
		

		void Resize(uint32_t newSize) 
		{

		}

		void Reserve(uint32_t capacity)
		{
			m_CurrentCapacity += capacity;
			T* newValues = (T*)malloc(sizeof(T) * m_CurrentCapacity);

			for (uint32_t i = 0; i < m_CurrentSize; ++i)
			{
				new (newValues + i) T(std::move(m_Values[i]));
			}

			delete m_Values;
			m_Values = newValues;
		}

		void Append(T element)
		{

			++m_CurrentSize;

			if (m_CurrentCapacity < m_CurrentSize)
			{
				++m_CurrentCapacity;
				//int* newValues = ::new int[m_CurrentCapacity];
				T* newValues = (T*)malloc(sizeof(T) * m_CurrentCapacity);

				for (uint32_t i = 0; i < m_CurrentSize - 1; ++i)
				{
					new (newValues + i) T(std::move(m_Values[i]));
				}

				new (newValues + m_CurrentSize - 1) T(std::move(element));
				delete m_Values;
				m_Values = newValues;
			}
			m_Values[m_CurrentSize - 1] = element;

		}

		void Append(T* elements, uint32_t count) 
		{

		}

		void Insert(uint32_t index) 
		{

		}

		void Delete(uint32_t index)
		{
			--m_CurrentSize;

			for (uint32_t i = index; i < m_CurrentSize; ++i)
			{
				m_Values[i] = std::move(m_Values[i + 1]);
			}
		}

		//iterator begin();
		//iterator end();

		inline uint32_t Size() { return m_CurrentSize; }
		inline uint32_t Reserved() { return m_CurrentCapacity - m_CurrentSize; }
		inline T Get(uint32_t index) { return m_Values[index]; }

		void* operator new(size_t size) // regular new
		{
			return ::new char[sizeof(T)];
		}

		void* operator new(size_t size, void* pWhere) {
			return pWhere;
		}

	private:
		uint32_t m_CurrentCapacity = 0;
		uint32_t m_CurrentSize = 0;
		T* m_Values;
	};
}