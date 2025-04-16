#include "Engine.h"
#include "Core/Macro.h"
#include "Core/Window/WindowSystem.h"
#include "Function/Render/RenderSystem.h"

namespace Taurus
{
	void TaurusEngine::StartEngine()
	{
        g_runtime_global_context.StartSystems();
		LOG_DEBUG("Engine Start!");
	}

	void TaurusEngine::ShutdownEngine()
	{
		LOG_DEBUG("Engine Shutdown!");
		g_runtime_global_context.ShutdownSystems();
	}

	void TaurusEngine::Run()
	{
		bool shouldClose = false;

		while (!shouldClose)
		{
			shouldClose = TickOneFrame(0);
		}
	}

	bool TaurusEngine::TickOneFrame(float delta_time)
	{
        LogicalTick(delta_time);
        RendererTick(delta_time);

		g_runtime_global_context.m_window_system->Tick();
		const bool should_window_close = g_runtime_global_context.m_window_system->ShouldClose();
		
		return should_window_close;
	}

    void TaurusEngine::LogicalTick(float delta_time)
    {
    }

	void TaurusEngine::RendererTick(float delta_time)
    {
        g_runtime_global_context.m_render_system->Tick(delta_time);
    }
}