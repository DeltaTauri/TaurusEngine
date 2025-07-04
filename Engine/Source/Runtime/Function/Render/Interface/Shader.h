#pragma once
#include <memory>
#include <string>
#include <glm/glm.hpp>

namespace Taurus
{
    class Shader
    {
    public:
        virtual ~Shader() = default;
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void SetInt(const std::string& name, int value) = 0;
        virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;

        static std::shared_ptr<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
    };
}