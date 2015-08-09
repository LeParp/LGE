#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>

#include "Mesh.h"

class Character
{
    public:
        Character(Mesh&& mesh)
        {
            mesh_ = std::move(mesh);
        }

        Mesh& mesh();
        Mesh const& mesh() const;

    private:
        Mesh mesh_;
};

#endif // CHARACTER_H
