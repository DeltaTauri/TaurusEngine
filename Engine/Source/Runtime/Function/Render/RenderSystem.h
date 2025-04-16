#pragma once
#include <memory>
#include "Function/Render/RenderPipline.h"
#include "Function/Render/Interface/RHI.h"

namespace Taurus
{
    class RenderSystem final
    {
    public:
        RenderSystem();
        ~RenderSystem() = default;
        void Initialize();
        void Tick(float delta_time);
        void Clear();
        std::shared_ptr<RHI> GetRHI() const { return m_RHI; }
        std::shared_ptr<RenderPipline> GetRenderPipline() const { return m_RenderPipline; }
    private:
        std::shared_ptr<RHI> m_RHI;
        std::shared_ptr<RenderPipline> m_RenderPipline;
    };

}