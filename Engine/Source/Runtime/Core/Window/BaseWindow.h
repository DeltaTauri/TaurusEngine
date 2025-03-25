#pragma once
#include <string>
#include <functional>
#include <memory>
#include <vector>

namespace Taurus {

	struct WindowProps
	{
		const char* Title;
		uint32_t Width;
		uint32_t Height;

		WindowProps(const char* title = "Taurus Engine",
			        uint32_t width = 1024,
			        uint32_t height = 768)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	typedef std::function<void(int, int, int, int)> onKeyFunc;
	typedef std::function<void(int, int, int)>      onMouseButtonFunc;
	typedef std::function<void(double, double)>     onCursorPosFunc;
	typedef std::function<void(double, double)>     onScrollFunc;
	typedef std::function<void(int, int)>           onWindowSizeFunc;

	class Window
	{
	public:

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;
		virtual bool ShouldClose() = 0;

		virtual int GetWidth() const = 0;
		virtual int GetHeight() const = 0;

		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;
		static std::unique_ptr<Window> Create(const WindowProps& props);

		std::vector<onKeyFunc>         m_onKeyFunc;
		std::vector<onMouseButtonFunc> m_onMouseButtonFunc;
		std::vector<onCursorPosFunc>   m_onCursorPosFunc;
		std::vector<onScrollFunc>      m_onScrollFunc;
		std::vector<onWindowSizeFunc>  m_onWindowSizeFunc;

	protected:
		void OnKey(int key, int scancode, int action, int mods)
		{
			for (auto& func : m_onKeyFunc)
				func(key, scancode, action, mods);
		}
		void OnMouseButton(int button, int action, int mods)
		{
			for (auto& func : m_onMouseButtonFunc)
				func(button, action, mods);
		}
		void OnCursorPos(double xpos, double ypos)
		{
			for (auto& func : m_onCursorPosFunc)
				func(xpos, ypos);
		}
		void OnScroll(double xoffset, double yoffset)
		{
			for (auto& func : m_onScrollFunc)
				func(xoffset, yoffset);
		}
		void OnWindowSize(int width, int height)
		{
			for (auto& func : m_onWindowSizeFunc)
				func(width, height);
		}
	};

}
