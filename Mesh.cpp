#include "Mesh.h"

Material& Mesh::material()
{
    return material_;
}

Material const& Mesh::material() const
{
    return material_;
}

std::vector<Vertex>& Mesh::vertices()
{
    return vertices_;
}

std::vector<Vertex> const& Mesh::vertices() const
{
    return vertices_;
}
