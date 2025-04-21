#pragma once
#include<glm/glm.hpp>

namespace Taurus
{
    class RenderCamera
    {
    public:
        RenderCamera() = default;
        ~RenderCamera() = default;
        
        void SetProjection(glm::vec4 param, float near = -1.0f, float far = 1.0f);
        void SetProjection(float fov, float aspect, float near = -1.0, float far = 1.0f);
        void SetPosition(const glm::vec3& position){ m_Position = position; UpdateViewMatrix(); }
        void SetPosition(float x, float y, float z) { m_Position = { x,y,z }; UpdateViewMatrix(); }
        void SetRotation(float rotation) { m_Rotation = rotation; UpdateViewMatrix(); }
        glm::vec3 GetPosition() const { return m_Position; }
        float GetRotation() const { return m_Rotation; }
        const glm::mat4 GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
    private:
        void UpdateViewMatrix();
    private:
        glm::mat4 m_ProjectionMatrix = 1.0f;
        glm::mat4 m_ViewMatrix = 1.0f;
        glm::mat4 m_ViewProjectionMatrix = 1.0f;
        glm::vec3 m_Position = { 0.0f,0.0f,0.0f };
        float m_Rotation = 0;
    };
}