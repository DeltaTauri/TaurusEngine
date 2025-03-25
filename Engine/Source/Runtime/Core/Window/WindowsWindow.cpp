#include <glad/glad.h>
#include "Core/Window/WindowsWindow.h"
#include "Core/Macro.h"

#include <imgui.h>
#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_opengl3.h>

namespace Taurus {
    SDL_GLContext gContext;

    unsigned int VBO, VAO;
    unsigned int shaderProgram;

    const char* vertexShaderSource = "#version 320 es\n"
        "layout (location = 0) in vec3 aPos;\n"
        "layout (location = 1) in vec3 aColor;\n"
        "out vec3 ourColor;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos, 1.0);\n"
        "   ourColor = aColor;\n"
        "}\0";

    const char* fragmentShaderSource = "#version 320 es\n"
        "precision mediump float;\n"
        "out vec4 FragColor;\n"
        "in vec3 ourColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(ourColor, 1.0f);\n"
        "}\n\0";


    bool initGL()
    {
        // vertex shader
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);
        // check for shader compile errors
        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            LOG_ERROR("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n", infoLog);
            return false;
        }
        // fragment shader
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);
        // check for shader compile errors
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            LOG_ERROR("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n", infoLog);
            return false;
        }
        // link shaders
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        // check for linking errors
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            LOG_ERROR("ERROR::SHADER::PROGRAM::LINKING_FAILED\n", infoLog);
            return false;
        }
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        float vertices[] = {
            // positions         // colors
             0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
             0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
        };

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
        // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
        // glBindVertexArray(0);

        glUseProgram(shaderProgram);
        return true;
    }

    bool initImgui(SDL_Window* window)
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        ImGui::StyleColorsDark();

        ImGui_ImplSDL3_InitForOpenGL(window, gContext);
        ImGui_ImplOpenGL3_Init("#version 100");
        return true;
    }

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

        if (SDL_Init(SDL_INIT_VIDEO) < 0)
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

                    if (SDL_GL_SetSwapInterval(1) < 0)
                    {
                        LOG_ERROR("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
                        success = false;
                    }

                    if (!initGL())
                    {
                        LOG_ERROR("Unable to initialize OpenGL!\n");
                        success = false;
                    }

                    if (!initImgui(m_NativeWindow))
                    {
                        LOG_ERROR("Unable to initialize Imgui!\n");
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
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteProgram(shaderProgram);

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL3_Shutdown();
        ImGui::DestroyContext();

        SDL_DestroyWindow(m_NativeWindow);
        m_NativeWindow = NULL;
        SDL_Quit();
	}

	void WindowsWindow::OnUpdate()
	{
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0)
		{
            ImGui_ImplSDL3_ProcessEvent(&e);
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

        //Render quad
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // render the triangle
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);


        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();
        bool show_demo_window = true;
        ImGui::ShowDemoWindow(&show_demo_window);
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        //Update screen
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
