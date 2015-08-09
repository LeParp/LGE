#include "Material.h"

Texture const& Material::diffuse_texture() const
{
    return diffuse_texture_;
}

Texture& Material::diffuse_texture()
{
    return diffuse_texture_;
}


Texture& Material::specular_texture()
{
    return specular_texture_;
}

Texture const& Material::specular_texture() const
{
    return specular_texture_;
}


glm::vec3 Material::diffuse_color() const
{
    return diffuse_color_;
}

glm::vec3& Material::diffuse_color()
{
    return diffuse_color_;
}


glm::vec3 Material::specular_color() const
{
    return specular_color_;
}

glm::vec3& Material::specular_color()
{
    return specular_color_;
}


float& Material::shininess()
{
    return shininess_;
}

float Material::shininess() const
{
    return shininess_;
}


bool& Material::textured()
{
    return textured_;
}

bool Material::textured() const
{
    return textured_;
}
