#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <unordered_map>

#include "Node.h"
#include "Mesh.h"
#include "Light.h"
#include "Camera.h"

#include "ContainerProxy.h"

class Model
{
    public:
        Model() = default;

        void add_node(std::string name, Node&& new_node);
        void add_mesh(std::string name, Mesh&& new_mesh);
        void add_light(std::string name, Light&& new_light);
        void add_camera(std::string name, Camera&& new_camera);

        Node& node(std::string name);
        Mesh& mesh(std::string name);
        Light& light(std::string name);
        Camera& camera(std::string name);

        UMapProxy<std::string, Node> nodes();
        UMapProxy<std::string, Mesh> meshes();
        UMapProxy<std::string, Light> lights();
        UMapProxy<std::string, Camera> cameras();

    private:
        std::unordered_map<std::string, Node> nodes_;
        std::unordered_map<std::string, Mesh> meshes_;
        std::unordered_map<std::string, Light> lights_;
        std::unordered_map<std::string, Camera> cameras_;
};

#endif // MODEL_H
