#include "Function/Render/Interface/Texture.h"
#include "Function/Render/Interface/OpenGL/OpenGLTexture.h"

namespace Taurus
{
    std::shared_ptr<Texture2D> Texture2D::Create(const std::string& path)
    {
        return std::make_shared<OpenGLTexture2D>(path);
    }
}