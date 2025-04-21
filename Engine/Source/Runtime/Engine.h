#pragma once
#include <chrono>

namespace Taurus
{
	class TaurusEngine
	{
		friend class TaurusEditor;
	public:
		void StartEngine();
		void Run();
		void ShutdownEngine();
		bool TickOneFrame(float delta_time);

	private:
		void LogicalTick(float delta_time);
		void RendererTick(float delta_time);
		float CalculateDeltaTime();
	private:
		std::chrono::steady_clock::time_point m_last_tick_time_point{ std::chrono::steady_clock::now() };
	};
}