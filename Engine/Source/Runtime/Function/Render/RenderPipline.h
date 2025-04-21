#pragma once
#include <memory>
#include "Function/Render/Interface/RHI.h"
#include "Function/Render/RenderCamera.h"

namespace Taurus
{
    class Shader;

    class RenderPipline
    {
        friend class RenderSystem;
    public:
        virtual ~RenderPipline() = default;

        void BeginScene(const std::shared_ptr<RenderCamera>& camera);
        void EndScene();
        void Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4 model);
    private:
        std::shared_ptr<RHI> m_RHI;
        struct SceneData
        {
            glm::mat4 ViewProjectionMatrix;
        };
        std::unique_ptr<SceneData> m_SceneData = std::make_unique<SceneData>();
    };
}