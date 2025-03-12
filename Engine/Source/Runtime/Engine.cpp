#include <glad/glad.h>
#include <SDL3/SDL.h>
#include "Engine.h"
#include "Core/Log/Log.h"

namespace Taurus
{

    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
    //The window we'll be rendering to
    SDL_Window* gWindow = NULL;

    //OpenGL context
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
        // build and compile our shader program
        // ------------------------------------
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

        // set up vertex data (and buffer(s)) and configure vertex attributes
        // ------------------------------------------------------------------
        float vertices[] = {
            // positions         // colors
             0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
             0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 

        };

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
        // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
        // glBindVertexArray(0);

        // as we only have a single shader, we could also just activate our shader once beforehand if we want to 
        glUseProgram(shaderProgram);
        return true;
    }


    bool init()
    {
        //Initialization flag
        bool success = true;

        //Initialize SDL
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
            gWindow = SDL_CreateWindow("TaurusEngine", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
            if (gWindow == NULL)
            {
                LOG_ERROR("Window could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                //Create context
                gContext = SDL_GL_CreateContext(gWindow);
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
                        return false;
                    }

                    //Use Vsync
                    if (SDL_GL_SetSwapInterval(1) < 0)
                    {
                        LOG_ERROR("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
                    }

                    //Initialize OpenGL
                    if (!initGL())
                    {
                        LOG_ERROR("Unable to initialize OpenGL!\n");
                        success = false;
                    }
                }
            }
        }
        if (!success)
            LOG_ERROR("Failed to initialize!\n");
        return success;
    }

    void render()
    {
        // render
            // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // render the triangle
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    void close()
    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteProgram(shaderProgram);

        //Destroy window	
        SDL_DestroyWindow(gWindow);
        gWindow = NULL;

        //Quit SDL subsystems
        SDL_Quit();
    }

	void TaurusEngine::StartEngine()
	{
        Taurus::Log::Init();

		LOG_DEBUG("Engine Start!");
        init();
	}

	void TaurusEngine::ShutdownEngine()
	{
		LOG_DEBUG("Engine Shutdown!");
        close();
	}

	void TaurusEngine::Run()
	{
		//LOG_DEBUG("Engine is running!");
          //Main loop flag
        bool quit = false;

        //Event handler
        SDL_Event e;

        //While application is running
        while (!quit)
        {
            //Handle events on queue
            while (SDL_PollEvent(&e) != 0)
            {
                //User requests quit
                if (e.type == SDL_EVENT_QUIT)
                {
                    quit = true;
                }
            }

            //Render quad
            render();

            //Update screen
            SDL_GL_SwapWindow(gWindow);
        }
	}

}