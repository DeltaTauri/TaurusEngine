#pragma once
#include <memory>
#include "Function/Render/Interface/RHI.h"

namespace Taurus
{
    class Shader;

    class RenderPipline
    {
        friend class RenderSystem;
    public:
        virtual ~RenderPipline() = default;

        void BeginScene();
        void EndScene();
        void Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader);
    private:
        std::shared_ptr<RHI> m_RHI;
    };
}