#include "Function/Render/Interface/VertexArray.h"
#include "Function/Render/Interface/OpenGL/OpenGLVertexArray.h"

namespace Taurus
{
    std::shared_ptr<VertexArray> VertexArray::Create()
    {
        return std::make_shared<OpenGLVertexArray>();
    }
}
