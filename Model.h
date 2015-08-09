#ifndef MODEL_H
#define MODEL_H

#include <unordered_map>
#include <string>

#include "Node.h"
#include "Mesh.h"
#include "Light.h"
#include "Camera.h"

class Model
{
    public:
        Model() = default;

        void add_node(std::string name, Node&& new_node);
        void add_mesh(std::string name, Mesh&& new_mesh);
        void add_light(std::string name, Light&& new_light);
        void add_camera(std::string name, Camera&& new_camera);

        Node&& get_node(std::string name);
        Mesh&& get_mesh(std::string name);
        Light&& get_light(std::string name);
        Camera&& get_camera(std::string name);

        std::unordered_map<std::string, Node>&& get_nodes();
        std::unordered_map<std::string, Mesh>&& get_meshes();
        std::unordered_map<std::string, Light>&& get_lights();
        std::unordered_map<std::string, Camera>&& get_cameras();

    private:
        std::unordered_map<std::string, Node> nodes_;
        std::unordered_map<std::string, Mesh> meshes_;
        std::unordered_map<std::string, Light> lights_;
        std::unordered_map<std::string, Camera> cameras_;
};

#endif // MODEL_H
