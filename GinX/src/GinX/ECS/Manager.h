#pragma once

#include <array>
#include <vector>
#include <bitset>

namespace mp
{
	template<typename T>
	using unwrap = typename T::type;
}

namespace GinX
{
	struct Transform
	{

	};

	struct QuadRenderer
	{

	};



	constexpr size_t maxEntities = 10000;

	class Entity
	{
	public:
		Entity();
		Entity(const std::string& name);
		~Entity();

		inline std::string& GetName() { return m_Name; }
		inline uint32_t GetID() { return m_UniqueIdentifier; }
	private:
		std::string m_Name;
		uint32_t m_ComponentBitmask;
		uint32_t m_UniqueIdentifier;
	};

	class Manager
	{
	private:
		template< typename TComponent>
		auto& access_component(uint32_t eid) 
		{
			return eid;
		}

	public:
		Manager();
		~Manager();

		uint32_t CreateEntity();
		uint32_t CreateEntity(const std::string& name);
		void RemoveEntity(uint32_t id);


		template<typename TComponentTag>
		auto& access_component(TComponentTag, uint32_t eid) {
			return access_component<mp::unwrap<TComponentTag>>(eid);
		}

		inline Entity& GetEntity(uint32_t id) { return (*m_Entities)[id]; }

	private:
		//vector would be better for iterating over all entities. 
		//+ useful for comparing all entity bit-masks and getting matching indizes
		std::vector<Entity> m_EntitiesVec;
		std::unordered_map<uint32_t, Entity>* m_Entities;
		std::array<Transform, maxEntities>* m_Transforms;
		std::array<QuadRenderer, maxEntities>* m_QuadRenderers;
	};
}