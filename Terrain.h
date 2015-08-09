#ifndef TERRAIN_H
#define TERRAIN_H

#include <string>
#include <vector>

#include "Model.h"
#include "Mesh.h"
#include "Light.h"

class Terrain
{
    public:
        Terrain(Model&& model);

        Mesh& mesh();
        Mesh const& mesh() const;

        std::vector<Light>& lights();
        std::vector<Light> const& lights() const;

    private:
        Mesh mesh_;
        std::vector<Light> lights_;
};

#endif // TERRAIN_H
