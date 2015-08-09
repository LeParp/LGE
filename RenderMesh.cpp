#include "RenderMesh.h"

RenderMesh::RenderMesh(Mesh const& mesh) :
    mesh_(mesh),
    material_(mesh_.material())
{
    glGenVertexArrays(1, &vertex_array_);
    glGenBuffers(1, &vertex_buffer_);

    glBindVertexArray(vertex_array_);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);

    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mesh_.vertices().size(), mesh_.vertices().data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoords));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

glm::mat4 RenderMesh::model() const
{
    return mesh_.model();
}

RenderMaterial& RenderMesh::material()
{
    return material_;
}

void RenderMesh::render()
{
    glBindVertexArray(vertex_array_);
    glDrawArrays(GL_TRIANGLES, 0, mesh_.vertices().size());
    glBindVertexArray(0);
}
