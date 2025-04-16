#include <glad/glad.h>
#include "Core/Window/WindowsWindow.h"
#include "Core/Macro.h"

namespace Taurus {
    SDL_GLContext gContext;

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
        bool success = true;

        if (!SDL_Init(SDL_INIT_VIDEO))
        {
            LOG_ERROR("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            //Use OpenGL 3.1 core
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);

            //Create window
            m_NativeWindow = SDL_CreateWindow(props.Title, props.Width, props.Height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
            if (m_NativeWindow == NULL)
            {
                LOG_ERROR("Window could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                //Create context
                gContext = SDL_GL_CreateContext(m_NativeWindow);
                if (gContext == NULL)
                {
                    LOG_ERROR("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
                    success = false;
                }
                else
                {
                    if (!gladLoadGLES2Loader((GLADloadproc)SDL_GL_GetProcAddress))
                    {
                        LOG_ERROR("Failed to initialize GLAD");
                        success = false;
                    }

                    if (!SDL_GL_SetSwapInterval(1))
                    {
                        LOG_ERROR("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
                        success = false;
                    }
                }
            }
        }
        if (!success)
            LOG_ERROR("Failed to initialize!\n");
	}

	void WindowsWindow::Shutdown()
	{
        SDL_DestroyWindow(m_NativeWindow);
        m_NativeWindow = NULL;
        SDL_Quit();
	}

	void WindowsWindow::OnUpdate()
	{
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0)
		{
			switch (e.type)
			{
			case SDL_EVENT_QUIT:
				m_Quit = true;
				break;
			case SDL_EVENT_KEY_DOWN:
			case SDL_EVENT_KEY_UP:
				OnKey(e.key.key, e.key.scancode, e.key.down ? 1 : 0, e.key.mod);
				break;
			case SDL_EVENT_MOUSE_BUTTON_DOWN:
			case SDL_EVENT_MOUSE_BUTTON_UP:
				OnMouseButton(e.button.button, e.button.down ? 1 : 0, 0);
				break;
			case SDL_EVENT_MOUSE_MOTION:
				OnCursorPos(e.motion.x, e.motion.y);
				break;
			case SDL_EVENT_MOUSE_WHEEL:
				OnScroll(e.wheel.x, e.wheel.y);
				break;
			case SDL_EVENT_WINDOW_RESIZED:
				SDL_GetWindowSize(m_NativeWindow, &Width, &Height);
				OnWindowSize(Width, Height);
				break;
			default:
				break;
			}
		}

        SDL_GL_SwapWindow(m_NativeWindow);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			SDL_SetWindowSurfaceVSync(m_NativeWindow, SDL_WINDOW_SURFACE_VSYNC_ADAPTIVE);
		else
            SDL_SetWindowSurfaceVSync(m_NativeWindow, SDL_WINDOW_SURFACE_VSYNC_DISABLED);
	}

	bool WindowsWindow::IsVSync() const
	{
        int ret = 0;
		SDL_GetWindowSurfaceVSync(m_NativeWindow, &ret);
		return ret == SDL_WINDOW_SURFACE_VSYNC_ADAPTIVE;
	}
    
}
