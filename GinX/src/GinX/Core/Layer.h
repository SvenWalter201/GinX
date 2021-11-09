#pragma once

#include "GinX/Core/Core.h"
#include "GinX/Core/Timestep.h"
#include "GinX/Events/Event.h"

namespace GinX
{
	class GINX_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(TimeStep ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& evemt) {}
	
		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};

}

