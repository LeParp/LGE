#ifndef PHYSICMESH_H
#define PHYSICMESH_H

#include <glm/vec3.hpp>

class Mesh;
class PhysicMesh
{
    public:
        PhysicMesh(Mesh& mesh);

        void apply(glm::vec3 const& force);

        glm::vec3 forces();
        glm::vec3 speed();

        void elapsed(float time);

    private:
        Mesh& mesh_;

        float mass_;
        glm::vec3 forces_;
        glm::vec3 speed_;
};

#endif // PHYSICMESH_H
