#ifndef EVENTS_H
#define EVENTS_H

#include <SFML/Window/Keyboard.hpp>
#include <glm/vec3.hpp>

#include "Entity.h"
#include "Node.h"
#include "Mesh.h"
#include "Light.h"
#include "Camera.h"

struct GameStarted
{

};

struct GamePaused
{

};

struct GameResumed
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

using Key = sf::Keyboard::Key;
struct KeyPressed
{
    Key key;
};

struct Play
{
    Entity entity;
};

struct SetPlayable
{
    Entity entity;
    Node& body;
    Node& vertical_rotor;
    Node& horizontal_rotor;
};

struct SetGround
{
    Entity entity;
    Mesh& mesh;
};

struct SetDynamicBody
{
    Entity entity;
    Mesh& mesh;
    Node& root;
};

struct Impulse
{
    Entity entity;
    glm::vec3 amount;
};

struct Collided
{
    Entity entity;
};

struct SetRenderable
{
    Entity entity;
    Mesh& mesh;
};

struct SetLighter
{
    Entity entity;
    Light& light;
};

struct SetViewer
{
    Entity entity;
    Camera& camera;
};

struct View
{
    Entity entity;
};

#endif // EVENTS_H
