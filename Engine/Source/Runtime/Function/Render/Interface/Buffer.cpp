#include "Function/Render/Interface/Buffer.h"
#include "Function/Render/Interface/OpenGL/OpenGLBuffer.h"

namespace Taurus {
    std::shared_ptr<VertexBuffer> VertexBuffer::Create(float* data, uint32_t size)
    {
        return std::make_shared<OpenGLVertexBuffer>(data, size);
    }

    std::shared_ptr<IndexBuffer> IndexBuffer::Create(uint32_t* data, uint32_t size)
    {
        return std::make_shared<OpenGLIndexBuffer>(data, size);
    }
}
