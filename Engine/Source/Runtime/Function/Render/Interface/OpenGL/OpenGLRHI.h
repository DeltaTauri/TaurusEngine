#pragma once
#include "Function/Render/Interface/RHI.h"
#include <memory>

namespace Taurus
{
    class OpenGLRHI : public RHI
    {
    public:
        OpenGLRHI() = default;
        ~OpenGLRHI() = default;
        void SetClearColor(float r, float g, float b, float a) override;
        void Clear() override;
        void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray, uint32_t indexCount = 0) override;
    };
}