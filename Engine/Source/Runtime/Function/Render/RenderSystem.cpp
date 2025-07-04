#include "Function/Render/RenderSystem.h"
#include "Function/Render/Interface/Shader.h"
#include "Function/Render/Interface/VertexArray.h"
#include "Function/Render/Interface/Texture.h"
#include "Function/Global/GlobalContext.h"
#include "Function/Input/InputSystem.h"
#include "Function/Input/KeyCode.h"

namespace Taurus
{
    const char* vertexShaderSource = "#version 320 es\n"
        "layout (location = 0) in vec3 aPos;\n"
        "layout (location = 1) in vec2 a_TexCoord;\n"
        "uniform mat4 u_ViewProjection;\n"
        "uniform mat4 u_Model;\n"
        "out vec2 ourUv;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = u_ViewProjection * u_Model * vec4(aPos, 1.0);\n"
        "   ourUv = a_TexCoord;\n"
        "}\0";

    const char* fragmentShaderSource = "#version 320 es\n"
        "precision mediump float;\n"
        "out vec4 FragColor;\n"
        "in vec2 ourUv;\n"
        "uniform sampler2D u_Texture;\n"
        "void main()\n"
        "{\n"
        //"   FragColor = vec4(ourUv, 1.0f, 1.0f);\n"
        "   FragColor = texture(u_Texture, ourUv);\n"
        "}\n\0";

    std::shared_ptr<Shader> m_Shader;
    std::shared_ptr<VertexArray> m_QuadVertexArray;
    std::shared_ptr<Texture> m_Texture;

    void InitData()
    {
        m_Shader = Shader::Create("OpenGLShader", vertexShaderSource, fragmentShaderSource);

        float vertices[] = {
            //position           uv
             -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
              0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
              0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
             -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
        };
        unsigned int quadIndices[6] = { 0,1,2,2,3,0 };
        BufferLayout layout = {
            {ShaderDataType::Float3, "a_Position"},
            {ShaderDataType::Float2, "a_TexCoord"},
        };

        std::shared_ptr<VertexBuffer> vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
        vertexBuffer->SetLayout(layout);

        m_QuadVertexArray = VertexArray::Create();
        m_QuadVertexArray->AddVertexBuffer(vertexBuffer);
        std::shared_ptr<IndexBuffer> m_quadIndexBuffer = IndexBuffer::Create(quadIndices, sizeof(quadIndices));
        m_QuadVertexArray->SetIndexBuffer(m_quadIndexBuffer);

        m_Texture = Texture2D::Create("Checkerboard.png");
        m_Texture->Bind(0);

        m_Shader->Bind();
        m_Shader->SetInt("u_Texture", 0);
    }

    RenderSystem::RenderSystem()
    {
        Initialize();
    }

    void RenderSystem::Initialize()
    {
        InitData();
        m_RHI = RHI::Create();
        m_RenderPipline = std::make_shared<RenderPipline>();
        m_RenderPipline->m_RHI = m_RHI;
        m_RenderCamera = std::make_shared<RenderCamera>();
        m_RenderCamera->SetProjection({ -1.2f, 1.2f, -0.9f,0.9f });
        m_RenderCamera->SetPosition(0, 0, 0);
    }

    void RenderSystem::Tick(float delta_time)
    {
        glm::vec3 cameraPos = m_RenderCamera->GetPosition();
        if (g_runtime_global_context.m_input_system->IsKeyPressed(Key::KEY_W))
            cameraPos.y += 0.5f * delta_time;
        if (g_runtime_global_context.m_input_system->IsKeyPressed(Key::KEY_S))
            cameraPos.y -= 0.5f * delta_time;
        if (g_runtime_global_context.m_input_system->IsKeyPressed(Key::KEY_A))
            cameraPos.x -= 0.5f * delta_time;
        if (g_runtime_global_context.m_input_system->IsKeyPressed(Key::KEY_D))
            cameraPos.x += 0.5f * delta_time;
        m_RenderCamera->SetPosition(cameraPos);

        float camearaRot = m_RenderCamera->GetRotation();
        if (g_runtime_global_context.m_input_system->IsKeyPressed(Key::KEY_Q))
            camearaRot -= 10 * delta_time;
        if (g_runtime_global_context.m_input_system->IsKeyPressed(Key::KEY_E))
            camearaRot += 10 * delta_time;
        m_RenderCamera->SetRotation(camearaRot);

        m_RHI->SetClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        m_RHI->Clear();
        m_RenderPipline->BeginScene(m_RenderCamera);
        m_RenderPipline->Submit(m_QuadVertexArray, m_Shader, glm::mat4(1.0f));
        m_RenderPipline->EndScene();
    }

    void RenderSystem::Clear()
    {
      
    }
}