#include "Node.h"

#include <algorithm>
#include <cassert>

#include <glm/gtc/matrix_transform.hpp>

Node::Node() :
    parent_(nullptr)
{

}

Node::Node(Node& parent) :
    parent_(&parent)
{
    parent_->children_.push_front(this);
}

Node::Node(Node&& other)
{
    *this = std::move(other);
}

Node::~Node()
{
    // S'il a un parent, on attache les enfants au parent
    if(parent_)
    {
        parent_->children_.remove_if([this](Node* child_ptr){return child_ptr == this;});

        for(Node* child : children_)
            child->attach(*parent_);
    }

    // Sinon on détache les enfants
    else
    {
        for(Node* child : children_)
            child->detach();
    }
}


Node& Node::operator=(Node&& other)
{
    parent_ = other.parent_;
    translation_ = std::move(other.translation_);
    rotation_ = std::move(other.rotation_);
    children_ = std::move(other.children_);
    other.children_.clear(); // Utilisé dans le destructeur

    // On met les pointeurs des enfants à jour
    for(Node* child : children_)
        child->parent_ = this;

    // On me le pointeur du parent à jour
    if(parent_)
    {
        for(Node*& parent_child : parent_->children_)
        {
            if(parent_child == &other)
                parent_child = this;
        }
    }

    return *this;
}


Node& Node::parent()
{
    assert(parent_);
    return *parent_;
}


void Node::attach(Node& parent)
{
    detach();

    glm::mat4 m = glm::inverse(parent.model()) * model();
    translation_ = glm::vec3(m[3]);
    rotation_ = glm::mat3(m);

    parent_ = &parent;
    parent_->children_.push_front(this);
}

void Node::detach()
{
    if(parent_)
    {
        glm::mat4 m = model();
        translation_ = glm::vec3(m[3]);
        rotation_ = glm::mat3(m);

        parent_->children_.remove_if([this](Node* child_ptr){return child_ptr == this;});
        parent_ = nullptr;
    }
}


glm::mat4 Node::model() const
{
    if(parent_)
        return parent_->model() * local_model();

    else
        return local_model();
}


void Node::move(glm::vec3 value)
{
    translation_ += rotation_ * value;
}

void Node::translate(glm::vec3 value)
{
    translation_ += value;
}

void Node::rotate(glm::vec3 axis, float angle)
{
    rotation_ = glm::mat3(glm::rotate(glm::mat4(rotation_), angle, axis));
}


glm::mat4 Node::local_model() const
{
    return {rotation_[0][0], rotation_[0][1], rotation_[0][2], 0.0,
            rotation_[1][0], rotation_[1][1], rotation_[1][2], 0.0,
            rotation_[2][0], rotation_[2][1], rotation_[2][2], 0.0,
            translation_[0], translation_[1], translation_[2], 1.0};
    //return glm::translate(glm::mat4(), translation_) * glm::mat4(rotation_);
    //return glm::mat4(rotation_) * glm::translate(glm::mat4(), translation_);
}
