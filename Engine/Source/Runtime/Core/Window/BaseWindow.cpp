#include "Core/Window/BaseWindow.h"
#include "Core/Macro.h"

#ifdef TAURUS_WINDOWS
#include "Core/Window/WindowsWindow.h"
#endif
namespace Taurus
{
	std::unique_ptr<Window> Window::Create(const WindowProps& props)
	{
	#ifdef TAURUS_WINDOWS
		return std::make_unique<WindowsWindow>(props);
	#else
		TAURUS_ASSERT(false, "Unknown platform!");
		return nullptr;
	#endif
	}

}