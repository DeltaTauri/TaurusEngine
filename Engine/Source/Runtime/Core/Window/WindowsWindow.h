#pragma once

#include "Core/Window/BaseWindow.h"
#include <SDL3/SDL.h>

namespace Taurus {

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;
		bool ShouldClose() override{ return m_Quit; }

		int GetWidth() const override { return Width; }
		int GetHeight() const override { return Height; }

		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		virtual void* GetNativeWindow() const { return m_NativeWindow; }
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		SDL_Window* m_NativeWindow;
		bool m_Quit = false;
		int Width, Height;
	};

}