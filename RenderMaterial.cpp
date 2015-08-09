#include "RenderMaterial.h"

RenderMaterial::RenderMaterial(Material const& material) :
    material_(material),
    diffuse_(material_.diffuse_texture()),
    specular_(material.specular_texture())
{

}

void RenderMaterial::bind(GLuint diffuse_slot, GLuint specular_slot)
{
    glActiveTexture(GL_TEXTURE0 + diffuse_slot);
    diffuse_.bind();

    glActiveTexture(GL_TEXTURE0 + specular_slot);
    specular_.bind();
}

glm::vec3 RenderMaterial::diffuse_color() const
{
    return material_.diffuse_color();
}

glm::vec3 RenderMaterial::specular_color() const
{
    return material_.specular_color();
}

float RenderMaterial::shininess() const
{
    return material_.shininess();
}

bool RenderMaterial::textured() const
{
    return material_.textured();
}
