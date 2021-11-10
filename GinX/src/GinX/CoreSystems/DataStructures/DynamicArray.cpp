#include "gxpch.h"
#include "DynamicArray.h"

namespace GinX
{
	void DynamicArray::Append(int element)
	{
		
		++m_CurrentSize;
		
		if (m_CurrentCapacity < m_CurrentSize)
		{
			++m_CurrentCapacity;
			//int* newValues = ::new int[m_CurrentCapacity];
			int* newValues =  (int*)malloc(sizeof(int) * m_CurrentCapacity);
		
			for (uint32_t i = 0; i < m_CurrentSize - 1; ++i)
			{
				new (newValues + i) int(m_Values[i]);
			}

			new (newValues + m_CurrentSize - 1) int(element);
			delete m_Values;
			m_Values = newValues;
		}
#
		m_Values[m_CurrentSize - 1] = element;
		
	}

	void DynamicArray::Append(int* elements, uint32_t count)
	{

	}

	void DynamicArray::Insert(uint32_t index)
	{

	}

	void DynamicArray::Delete(uint32_t index)
	{
		--m_CurrentSize;

		for (uint32_t i = index; i < m_CurrentSize; ++i)
		{
			m_Values[i] = m_Values[i + 1];
		}
		
		m_Values[m_CurrentSize] = 0;
	}

	/*
	GinX::DynamicArray::iterator DynamicArray::begin()
	{

	}

	GinX::DynamicArray::iterator DynamicArray::end()
	{

	}
	*/

	DynamicArray::~DynamicArray()
	{

	}

	void DynamicArray::Resize(uint32_t newSize)
	{

	}

	void DynamicArray::Reserve(uint32_t newCapacity)
	{

	}

	DynamicArray::DynamicArray()
		: m_CurrentSize(0), m_CurrentCapacity(0), m_Values(new int[0])
	{

	}

	DynamicArray::DynamicArray(uint32_t initialCapacity)
		: m_CurrentSize(0), m_CurrentCapacity(initialCapacity), m_Values(new int[initialCapacity])
	{

	}
}