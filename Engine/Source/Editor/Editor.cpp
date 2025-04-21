#include "Editor.h"
#include "Engine.h"
#include "Function/Global/GlobalContext.h"
#include "Core/Window/WindowSystem.h"

namespace Taurus
{
	TaurusEditor::TaurusEditor() {}

	TaurusEditor::~TaurusEditor() {}

	void TaurusEditor::Initialize(TaurusEngine* engine_runtime)
	{
		m_engine_runtime = engine_runtime;
	}

	void TaurusEditor::ShutDown()
	{
		
	}

	void TaurusEditor::Run()
	{
		bool shouldClose = false;

		while (!shouldClose)
		{
			const float delta_time = m_engine_runtime->CalculateDeltaTime();
			shouldClose = m_engine_runtime->TickOneFrame(delta_time);
		}
	}
}