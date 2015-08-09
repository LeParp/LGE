#include "Object.h"

Object::Object(Node& parent) :
    Node(parent)
{

}

Node& Object::node()
{
    return *this;
}

