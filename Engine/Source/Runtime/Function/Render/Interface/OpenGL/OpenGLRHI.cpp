#include "Function/Render/Interface/OpenGL/OpenGLRHI.h"
#include <glad/glad.h>
#include "Function/Render/Interface/VertexArray.h"

namespace Taurus
{
    void OpenGLRHI::SetClearColor(float r, float g, float b, float a)
    {
        glClearColor(r, g, b, a);
    }

    void OpenGLRHI::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRHI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray, uint32_t indexCount)
    {
        glDrawElements(GL_TRIANGLES, indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }

}