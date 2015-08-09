#ifndef MESH_H
#define MESH_H

#include <map>
#include <vector>

#include <glm/mat4x4.hpp>

#include "Object.h"
#include "Material.h"
#include "Vertex.h"

class Mesh : public Object
{
    public:
        using Object::Object;

        Material& material();
        Material const& material() const;

        std::vector<Vertex>& vertices();
        std::vector<Vertex> const& vertices() const;

    private:
        Material material_;
        std::vector<Vertex> vertices_;
        //std::vector<Node> node_vertices_;
};

#endif // MESH_H
