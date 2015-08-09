#include "Terrain.h"

Terrain::Terrain(Model&& model)
{
    mesh_ = model.get_mesh("Ground");

    auto&& lights = model.get_lights();
    for(auto it = lights.begin(); it != lights.end(); ++it)
        lights_.push_back(std::move(it->second));
}


Mesh& Terrain::mesh()
{
    return mesh_;
}

Mesh const& Terrain::mesh() const
{
    return mesh_;
}


std::vector<Light>& Terrain::lights()
{
    return lights_;
}

std::vector<Light> const& Terrain::lights() const
{
    return lights_;
}
