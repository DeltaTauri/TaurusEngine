#include "Function/Render/Interface/OpenGL/OpenGLVertexArray.h"
#include "RenderPipline.h"
#include "Function/Render/Interface/Shader.h"

namespace Taurus
{
    void Taurus::RenderPipline::BeginScene()
    {
    }

    void Taurus::RenderPipline::EndScene()
    {
    }

    void Taurus::RenderPipline::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader)
    {
        shader->Bind();
        vertexArray->Bind();
        m_RHI->DrawIndexed(vertexArray);
    }
}
