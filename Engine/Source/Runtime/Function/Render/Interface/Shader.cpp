#include "Function/Render/Interface/Shader.h"
#include "Function/Render/Interface/OpenGL/OpenGLShader.h"

namespace Taurus
{
    std::shared_ptr<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
    }
    
}