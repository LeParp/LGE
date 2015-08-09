#ifndef RENDERMATERIAL_H
#define RENDERMATERIAL_H

#include <GL/glew.h>

#include "Material.h"
#include "RenderTexture.h"

class RenderMaterial
{
    public:
        RenderMaterial(Material const& material);
        RenderMaterial(Material&& material) = delete;

        void bind(GLuint diffuse_slot, GLuint specular_slot);

        glm::vec3 diffuse_color() const;
        glm::vec3 specular_color() const;
        float shininess() const;
        bool textured() const;

    private:
        Material const& material_;
        RenderTexture diffuse_, specular_;
};

#endif // RENDERMATERIAL_H
