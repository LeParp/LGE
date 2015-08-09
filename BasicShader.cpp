#include "BasicShader.h"

#include <glm/gtc/type_ptr.hpp>

BasicShader::BasicShader()
{
    std::string vertex_source = R"(
        #version 330

        layout (location = 0) in vec3 vertex_position;
        layout (location = 1) in vec3 vertex_color;

        out vec3 fragment_color;

        uniform mat4 Projection, View, Model;

        void main()
        {
            fragment_color = vertex_color;
            gl_Position = Projection * View * Model * vec4(vertex_position, 1.0);
        }
    )";

    std::string fragment_source = R"(
        #version 330

        in vec3 fragment_color;

        out vec4 final_color;

        void main()
        {
            final_color = vec4(fragment_color, 1.0);
        }
    )";

    compile(vertex_source, fragment_source);

    projection_location_ = glGetUniformLocation(program_, "Projection");
    view_location_ = glGetUniformLocation(program_, "View");
    model_location_ = glGetUniformLocation(program_, "Model");
}


void BasicShader::projection(glm::mat4 value)
{
    glUniformMatrix4fv(projection_location_, 1, GL_FALSE, glm::value_ptr(value));
}

void BasicShader::view(glm::mat4 value)
{
    glUniformMatrix4fv(view_location_, 1, GL_FALSE, glm::value_ptr(value));
}

void BasicShader::model(glm::mat4 value)
{
    glUniformMatrix4fv(model_location_, 1, GL_FALSE, glm::value_ptr(value));
}
