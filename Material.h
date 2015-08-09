#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/vec3.hpp>

#include "Texture.h"

class Material
{
    public:
        Material() = default;

        Texture& diffuse_texture();
        Texture const& diffuse_texture() const;

        Texture& specular_texture();
        Texture const& specular_texture() const;

        glm::vec3& diffuse_color();
        glm::vec3 diffuse_color() const;

        glm::vec3& specular_color();
        glm::vec3 specular_color() const;

        float& shininess();
        float shininess() const;

        bool& textured();
        bool textured() const;

    private:
        Texture diffuse_texture_, specular_texture_;
        glm::vec3 diffuse_color_, specular_color_;
        float shininess_;
        bool textured_;
};

#endif // MATERIAL_H
