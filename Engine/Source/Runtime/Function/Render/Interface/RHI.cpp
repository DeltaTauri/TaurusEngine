#include "Function/Render/Interface/RHI.h"
#include "Function/Render/Interface/OpenGL/OpenGLRHI.h"

namespace Taurus
{
    std::shared_ptr<RHI> RHI::Create()
    {
        return std::make_shared<OpenGLRHI>();
    }
}
