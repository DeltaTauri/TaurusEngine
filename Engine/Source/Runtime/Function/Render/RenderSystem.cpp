#include "Function/Render/RenderSystem.h"
#include "Function/Render/Interface/Shader.h"
#include "Function/Render/Interface/VertexArray.h"

namespace Taurus
{
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

    std::shared_ptr<Shader> m_Shader;
    std::shared_ptr<VertexArray> m_TriangleVertexArray;
    std::shared_ptr<VertexArray> m_QuadVertexArray;

    void InitData()
    {
        m_Shader = Shader::Create("OpenGLShader", vertexShaderSource, fragmentShaderSource);

        float vertices[] = {
            // positions         // colors
             0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
             0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   // top 
             0.0f, 0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom left
             0.5f, 0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom right
             0.0f, 0.75f, 0.0f,  1.0f, 0.0f, 0.0f,  // top left
             0.5f, 0.75f, 0.0f,  0.0f, 1.0f, 0.0f,  // top right
        };
        unsigned int triangleIndices[3] = { 0,1,2 };
        unsigned int quadIndices[6] = { 3,4,5,4,5,6 };
        BufferLayout layout = {
            {ShaderDataType::Float3, "a_Position"},
            {ShaderDataType::Float3, "a_Color"},
        };

        m_TriangleVertexArray = VertexArray::Create();
        std::shared_ptr<VertexBuffer> vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
        vertexBuffer->SetLayout(layout);
        m_TriangleVertexArray->AddVertexBuffer(vertexBuffer);
        std::shared_ptr<IndexBuffer> m_triangleIndexBuffer = IndexBuffer::Create(triangleIndices, sizeof(triangleIndices));
        m_TriangleVertexArray->SetIndexBuffer(m_triangleIndexBuffer);

        m_QuadVertexArray = VertexArray::Create();
        m_QuadVertexArray->AddVertexBuffer(vertexBuffer);
        std::shared_ptr<IndexBuffer> m_quadIndexBuffer = IndexBuffer::Create(quadIndices, sizeof(quadIndices));
        m_QuadVertexArray->SetIndexBuffer(m_quadIndexBuffer);
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
    }

    void RenderSystem::Tick(float delta_time)
    {
        m_RHI->SetClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        m_RHI->Clear();
        m_RenderPipline->BeginScene();
        m_RenderPipline->Submit(m_TriangleVertexArray, m_Shader);
        m_RenderPipline->Submit(m_QuadVertexArray, m_Shader);
        m_RenderPipline->EndScene();
    }

    void RenderSystem::Clear()
    {
      
    }
}