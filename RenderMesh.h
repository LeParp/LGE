#ifndef RENDERMESH_H
#define RENDERMESH_H

#include <GL/glew.h>

#include "Mesh.h"
#include "RenderMaterial.h"

class RenderMesh
{
    public:
        RenderMesh(Mesh const& mesh);
        RenderMesh(Mesh&& mesh) = delete;

        glm::mat4 model() const;
        RenderMaterial& material();

        void render();

    private:
        Mesh const& mesh_;
        RenderMaterial material_;
        GLuint vertex_array_, vertex_buffer_;
};

#endif // RENDERMESH_H
