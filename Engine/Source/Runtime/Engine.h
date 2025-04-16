#pragma once

namespace Taurus
{
	class TaurusEngine
	{
	public:
		void StartEngine();
		void Run();
		void ShutdownEngine();
		bool TickOneFrame(float delta_time);

	private:
		void LogicalTick(float delta_time);
		void RendererTick(float delta_time);
	};
}