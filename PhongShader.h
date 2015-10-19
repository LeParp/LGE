#ifndef PHONGSHADER_H
#define PHONGSHADER_H

#include <array>
#include <vector>

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

class PhongShader : public Shader
{
    public:
        PhongShader(unsigned lights_count);
        PhongShader(PhongShader&& other);
        PhongShader(PhongShader const& other) = delete;
        ~PhongShader() = default;

        PhongShader& operator=(PhongShader&& other);
        PhongShader& operator=(PhongShader const& other) = delete;

        void projection(glm::mat4 value);
        void view(glm::mat4 value);
        void model(glm::mat4 value);

        void light(auto& light, GLuint n) {
            glUniform3fv(array_locations_[LIGHT_POSITION][n], 1, glm::value_ptr(light.position()));
            glUniform3fv(array_locations_[LIGHT_COLOR][n], 1, glm::value_ptr(light.color()));
            glUniform3fv(array_locations_[LIGHT_ATTENUATIONS][n], 1, glm::value_ptr(light.attenuations()));
        }

        void material(auto& material) {
            if(material.textured())
                material.bind(MATERIAL_DIFFUSE, MATERIAL_SPECULAR);

            glUniform3fv(locations_[MATERIAL_DIFFUSE_COLOR], 1, glm::value_ptr(material.diffuse_color()));
            glUniform3fv(locations_[MATERIAL_SPECULAR_COLOR], 1, glm::value_ptr(material.specular_color()));
            glUniform1f(locations_[MATERIAL_SHININESS], material.shininess());
            glUniform1i(locations_[MATERIAL_TEXTURED], material.textured());
        }

    private:
        enum Uniforms
        {
            PROJECTION,
            VIEW,
            MODEL,

            MATERIAL_DIFFUSE_COLOR,
            MATERIAL_SPECULAR_COLOR,
            MATERIAL_SHININESS,
            MATERIAL_TEXTURED,

            UNIFORMS_COUNT
        };

        enum UniformArrays
        {
            LIGHT_POSITION,
            LIGHT_COLOR,
            LIGHT_ATTENUATIONS,

            UNIFORM_ARRAYS_COUNT
        };

        enum TextureSlots
        {
            MATERIAL_DIFFUSE,
            MATERIAL_SPECULAR
        };

        std::array<GLint, UNIFORMS_COUNT> locations_;
        std::array<std::vector<GLint>, UNIFORM_ARRAYS_COUNT> array_locations_;
};


#endif // PHONGSHADER_H
