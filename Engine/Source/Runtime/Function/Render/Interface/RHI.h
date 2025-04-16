#pragma once
#include <memory>

namespace Taurus
{
    class VertexArray;

    class RHI
    {
    public:
        virtual ~RHI() = default;
      
        virtual void SetClearColor(float r, float g, float b, float a) = 0;
        virtual void Clear() = 0;
        virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray, uint32_t indexCount = 0) = 0;

        static std::shared_ptr<RHI> Create();
    };
}