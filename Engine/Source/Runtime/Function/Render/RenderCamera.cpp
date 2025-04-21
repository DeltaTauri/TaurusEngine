#include "Function/Render/RenderCamera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Taurus
{
    void RenderCamera::SetProjection(glm::vec4 param, float near, float far)
    {
        m_ProjectionMatrix = glm::ortho(param.x, param.y, param.z, param.w, near, far);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void RenderCamera::SetProjection(float fov, float aspect, float near, float far)
    {
        m_ProjectionMatrix = glm::perspective(glm::radians(fov), aspect, near, far);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void RenderCamera::UpdateViewMatrix()
    {
        m_ViewMatrix = glm::inverse(glm::translate(glm::mat4(1.0f), m_Position) * glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), { 0, 0, 1 }));
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }
}