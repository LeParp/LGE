#include "PhysicMesh.h"

#include "Mesh.h"

PhysicMesh::PhysicMesh(Mesh& mesh) :
    mesh_(mesh),
    mass_(2.0),
    speed_(0.0)
{

}

void PhysicMesh::apply(glm::vec3 const& force)
{
    forces_ += force;
}

glm::vec3 PhysicMesh::forces()
{
    return forces_;
}

glm::vec3 PhysicMesh::speed()
{
    return speed_;
}

void PhysicMesh::elapsed(float time)
{
    speed_ += (time * forces_) / mass_;
    mesh_.move(speed_ * time);
}


