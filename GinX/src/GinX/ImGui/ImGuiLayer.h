#pragma once

#include "GinX/Layers/Layer.h"
#include "GinX/Events/ApplicationEvent.h"
#include "GinX/Events/MouseEvent.h"
#include "GinX/Events/KeyEvent.h"

namespace GinX
{
	class GINX_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;


		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
	};
}