#ifndef EVENTS_H
#define EVENTS_H

struct GameStarted
{

};

struct WindowCreated
{
    WindowCreated(unsigned w, unsigned h) : width(w), height(h) {}
    unsigned width, height;
};

struct WindowResized
{
    WindowResized(unsigned w, unsigned h) : width(w), height(h) {}
    unsigned width, height;
};

class Mesh;
struct MeshAdded
{
    MeshAdded(Mesh& m) : mesh(m) {}
    Mesh& mesh;
};

class Light;
struct LightAdded
{
    LightAdded(Light& l) : light(l) {}
    Light& light;
};

class Camera;
struct CameraAdded
{
    CameraAdded(Camera& c) : camera(c) {}
    Camera& camera;
};

class Player;
struct PlayerAdded
{
    PlayerAdded(Player& p) : player(p) {}
    Player& player;
};

#endif // EVENTS_H
