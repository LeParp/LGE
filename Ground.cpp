#include "Ground.h"

#include <cassert>

Ground::Ground() :
    terrain_(nullptr)
{

}


void Ground::set_terrain(Mesh& terrain)
{
    terrain_ = &terrain;
}

