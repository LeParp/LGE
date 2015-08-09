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


Node&& Model::get_node(std::string name)
{
    assert(nodes_.find(name) != nodes_.end());
    return std::move(nodes_[name]);
}

Mesh&& Model::get_mesh(std::string name)
{
    assert(meshes_.find(name) != meshes_.end());
    return std::move(meshes_[name]);
}

Light&& Model::get_light(std::string name)
{
    assert(lights_.find(name) != lights_.end());
    return std::move(lights_[name]);
}

Camera&& Model::get_camera(std::string name)
{
    assert(cameras_.find(name) != cameras_.end());
    return std::move(cameras_[name]);
}


std::unordered_map<std::string, Node>&& Model::get_nodes()
{
    return std::move(nodes_);
}

std::unordered_map<std::string, Mesh>&& Model::get_meshes()
{
    return std::move(meshes_);
}

std::unordered_map<std::string, Light>&& Model::get_lights()
{
    return std::move(lights_);
}

std::unordered_map<std::string, Camera>&& Model::get_cameras()
{
    return std::move(cameras_);
}
