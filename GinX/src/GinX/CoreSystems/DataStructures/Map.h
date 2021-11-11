#pragma once

namespace GinX
{
	template<typename K, typename V>
	struct Pair
	{
		K Key;
		V Value;
	};

	template<typename K, typename V>
	class Map
	{
	public:

	private:
		uint32_t m_Reserved;
		uint32_t m_FullCount;
		uint32_t m_NumDeletedEntries;
		Pair<K, V>* m_Data;
	};

	static Map<int, float> m;

}