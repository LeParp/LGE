#ifndef OBJECT_H
#define OBJECT_H

#include "Node.h"

class Object : private Node
{
    public:
        Object() = default;
        Object(Node& parent);

        Node& node();
        using Node::parent;

        using Node::attach;
        using Node::detach;

        using Node::model;

        using Node::move;
        using Node::translate;
        using Node::rotate;

        using Node::position;
        using Node::orientation;
};

#endif // OBJECT_H
