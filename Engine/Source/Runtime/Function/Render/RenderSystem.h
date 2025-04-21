#pragma once
#include <memory>
#include "Function/Render/RenderPipline.h"
#include "Function/Render/Interface/RHI.h"
#include "Function/Render/RenderCamera.h"

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
        std::shared_ptr<RenderCamera> GetRenderCamera() const { return m_RenderCamera; }
    private:
        std::shared_ptr<RHI> m_RHI;
        std::shared_ptr<RenderPipline> m_RenderPipline;
        std::shared_ptr<RenderCamera> m_RenderCamera;
    };

}