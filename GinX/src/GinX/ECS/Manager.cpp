#include "gxpch.h"
#include "Manager.h"
/*
namespace GinX
{
	static uint32_t globalEntityID = 0;

	Entity::Entity() 
		: m_UniqueIdentifier(globalEntityID), m_ComponentBitmask(0), m_Name("")
	{
		++globalEntityID;
	}

	Entity::Entity(const std::string& name)
		: m_UniqueIdentifier(globalEntityID), m_ComponentBitmask(0), m_Name(name)
	{

	}

	Entity::~Entity()
	{
	}

	Manager::Manager() : 
		m_Transforms(new std::array<Transform, maxEntities>()), 
		m_QuadRenderers(new std::array<QuadRenderer, maxEntities>()),
		m_Entities(new std::unordered_map<uint32_t, Entity>())
	{

	}

	Manager::~Manager()
	{
		delete m_Transforms;
		delete m_QuadRenderers;
		delete m_Entities;
	}

	uint32_t Manager::CreateEntity()
	{
		Entity entity = Entity();
		uint32_t id = entity.GetID();
		(*m_Entities)[id] = entity;
		return id;
	}

	uint32_t Manager::CreateEntity(const std::string& name)
	{
		Entity entity = Entity(name);
		uint32_t id = entity.GetID();
		(*m_Entities)[id] = entity;
		return id;
	}

	void Manager::RemoveEntity(uint32_t id)
	{
		m_Entities->erase(id);
	}
}
*/