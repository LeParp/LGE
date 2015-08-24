#include "Model.h"

#include <cassert>

void Model::add_node(std::string name, Node&& new_node)
{
    assert(nodes_.find(name) == nodes_.end());
    nodes_[name] = std::move(new_node);
}

void Model::add_mesh(std::string name, Mesh&& new_mesh)
{
    assert(meshes_.find(name) == meshes_.end());
    meshes_[name] = std::move(new_mesh);
}

void Model::add_light(std::string name, Light&& new_light)
{
    assert(lights_.find(name) == lights_.end());
    lights_[name] = std::move(new_light);
}

void Model::add_camera(std::string name, Camera&& new_camera)
{
    assert(cameras_.find(name) == cameras_.end());
    cameras_[name] = std::move(new_camera);
}


Node& Model::node(std::string name)
{
    assert(nodes_.find(name) != nodes_.end());
    return nodes_[name];
}

Mesh& Model::mesh(std::string name)
{
    assert(meshes_.find(name) != meshes_.end());
    return meshes_[name];
}

Light& Model::light(std::string name)
{
    assert(lights_.find(name) != lights_.end());
    return lights_[name];
}

Camera& Model::camera(std::string name)
{
    assert(cameras_.find(name) != cameras_.end());
    return cameras_[name];
}


UMapProxy<std::string, Node> Model::nodes()
{
    return UMapProxy<std::string, Node>(nodes_);
}

UMapProxy<std::string, Mesh> Model::meshes()
{
    return UMapProxy<std::string, Mesh>(meshes_);
}

UMapProxy<std::string, Light> Model::lights()
{
    return UMapProxy<std::string, Light>(lights_);
}

UMapProxy<std::string, Camera> Model::cameras()
{
    return UMapProxy<std::string, Camera>(cameras_);
}
