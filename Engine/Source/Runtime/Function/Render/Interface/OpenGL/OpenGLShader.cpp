#include "Function/Render/Interface/OpenGL/OpenGLShader.h"
#include <glad/glad.h>
#include "Core/Macro.h"
#include <glm/gtc/type_ptr.hpp>

namespace Taurus
{
    OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        // vertex shader
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        const GLchar* source = vertexSrc.c_str();
        glShaderSource(vertexShader, 1, &source, NULL);
        glCompileShader(vertexShader);
        // check for shader compile errors
        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            LOG_ERROR("ERROR::SHADER::VERTEX::COMPILATION_FAILED:{}\n", infoLog);
            glDeleteShader(vertexShader);
            TAURUS_ASSERT(false);
        }
        // fragment shader
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        source = fragmentSrc.c_str();
        glShaderSource(fragmentShader, 1, &source, NULL);
        glCompileShader(fragmentShader);
        // check for shader compile errors
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            LOG_ERROR("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED:{}\n", infoLog);
            glDeleteShader(fragmentShader);
            TAURUS_ASSERT(false);
        }
        // link shaders
        m_ShaderProgram = glCreateProgram();
        glAttachShader(m_ShaderProgram, vertexShader);
        glAttachShader(m_ShaderProgram, fragmentShader);
        glLinkProgram(m_ShaderProgram);
        glGetProgramiv(m_ShaderProgram, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(m_ShaderProgram, 512, NULL, infoLog);
            LOG_ERROR("ERROR::SHADER::PROGRAM::LINK_FAILED:{}\n", infoLog);
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
            glDeleteProgram(m_ShaderProgram);
            TAURUS_ASSERT(false);
        }
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }
    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(m_ShaderProgram);
    }
    void OpenGLShader::Bind() const
    {
        glUseProgram(m_ShaderProgram);
    }
    void OpenGLShader::Unbind() const
    {
        glUseProgram(0);
    }
    void OpenGLShader::SetInt(const std::string& name, int value)
    {
        int location = glGetUniformLocation(m_ShaderProgram, name.c_str());
        if (location == -1)
        {
            LOG_ERROR("ERROR::SHADER::UNIFORM::NOT_FOUND\n", name);
            return;
        }
        glUniform1i(location, value);
    }
    void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value)
    {
        int location = glGetUniformLocation(m_ShaderProgram, name.c_str());
        if (location == -1)
        {
            LOG_ERROR("ERROR::SHADER::UNIFORM::NOT_FOUND\n", name);
            return;
        }
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
    }

}