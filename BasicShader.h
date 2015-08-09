#ifndef BASICSHADER_H
#define BASICSHADER_H

#include "Shader.h"

#include <glm/mat4x4.hpp>

class BasicShader : public Shader
{
    public:
        BasicShader();

        void projection(glm::mat4 value);
        void view(glm::mat4 value);
        void model(glm::mat4 value);

    private:
        GLint projection_location_, view_location_, model_location_;
};

#endif // BASICSHADER_H
