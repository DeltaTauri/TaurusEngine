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
	};
}