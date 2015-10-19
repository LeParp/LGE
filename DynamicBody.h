#ifndef DYNAMICBODY_H
#define DYNAMICBODY_H

#include <glm/vec3.hpp>

class Mesh;
class Node;
class DynamicBody
{
    public:
        DynamicBody(Mesh& mesh, Node& node);

        void impulse(const glm::vec3& amount);

        float mass();
        glm::vec3 velocity();
        glm::vec3 position();

        void move(float time);

    private:
        Mesh& mesh_;
        Node& node_;

        float mass_;
        glm::vec3 velocity_;

    friend bool collide(const DynamicBody& lhs, const DynamicBody& rhs);
};

#endif // DYNAMICBODY_H
