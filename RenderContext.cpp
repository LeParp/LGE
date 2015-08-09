#include "RenderContext.h"

#include <GL/glew.h>
#include <stdexcept>

RenderContext::RenderContext()
{
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK)
        throw std::runtime_error("Failed to initialize GLEW.");
}
