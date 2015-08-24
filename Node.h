#ifndef NODE_H
#define NODE_H

#include <forward_list>

#include <glm/vec3.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>

class Node
{
    public:
        Node();
        Node(Node& parent);
        Node(Node&& other);
        Node(Node const& other) = delete;
        ~Node();

        Node& operator=(Node&& other);
        Node& operator=(Node const& other) = delete;

        Node& parent();

        void attach(Node& parent); // Attach this node to a parent node
        void detach();

        glm::mat4 model() const;

        void move(glm::vec3 value); // Move the node in local space
        void translate(glm::vec3 value); // Move the node in parent space
        void rotate(glm::vec3 axis, float angle); // Axis in local space

        glm::vec3 position();
        glm::vec3 orientation(glm::vec3 local); // Transforms local to absolute orientation

    private:
        glm::mat4 local_model() const;

        Node* parent_;
        std::forward_list<Node*> children_;

        glm::vec3 translation_;
        glm::mat3 rotation_;
};

#endif // NODE_H
