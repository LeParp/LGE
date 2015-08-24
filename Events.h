#ifndef EVENTS_H
#define EVENTS_H

#include <glm/vec3.hpp>

class Node;
class Mesh;
class Light;
class Camera;

struct GameStarted
{

};

struct WindowCreated
{
    unsigned width, height;
};

struct WindowResized
{
    unsigned width, height;
};

struct SetPlayable
{
    unsigned entity_id;
    Node& body;
    Node& vertical_rotor;
    Node& horizontal_rotor;
};

struct SetDynamicBody
{
    unsigned entity_id;
    Mesh& mesh;
};

struct SetGround
{
    unsigned entity_id;
    Mesh& mesh;
};

struct Move
{
    unsigned entity_id;
    glm::vec3 movement;
};

struct Rotate
{
    unsigned entity_id;
    glm::vec3 axis;
    float angle;
};

struct ApplyForce
{
    unsigned entity_id;
    glm::vec3 force;
};

struct SetRenderable
{
    unsigned entity_id;
    Mesh& mesh;
};

struct SetLighter
{
    unsigned entity_id;
    Light& light;
};

struct SetViewer
{
    unsigned entity_id;
    Camera& camera;
};

struct Play
{
    unsigned entity_id;
};

struct View
{
    unsigned entity_id;
};

#endif // EVENTS_H
