#include "Function/Render/Interface/OpenGL/OpenGLVertexArray.h"
#include "RenderPipline.h"
#include "Function/Render/Interface/Shader.h"

namespace Taurus
{
    void Taurus::RenderPipline::BeginScene(const std::shared_ptr<RenderCamera>& camera)
    {
        m_SceneData->ViewProjectionMatrix = camera->GetViewProjectionMatrix();
    }

    void Taurus::RenderPipline::EndScene()
    {
    }

    void Taurus::RenderPipline::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4 model)
    {
        shader->Bind();
        shader->SetMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
        shader->SetMat4("u_Model", model);
        vertexArray->Bind();
        m_RHI->DrawIndexed(vertexArray);
    }
}
