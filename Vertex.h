#ifndef VERTEX_H
#define VERTEX_H

#include <array>

struct Vertex
{
    std::array<float, 3> position;
    std::array<float, 3> normal;
    std::array<float, 2> texcoords;
};

#endif // VERTEX_H
