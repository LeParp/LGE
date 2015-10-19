#include "Entity.h"

Entity::Entity() :
    id_(0)
{

}

Entity::Entity(EntitySeed& seed) :
    id_(seed.count_)
{
    seed.count_++;
}

bool Entity::is_null()
{
    return (id_ == 0);
}


bool operator==(const Entity& lhs, const Entity& rhs)
{
        return (lhs.id_ == rhs.id_);
}

bool operator!=(const Entity& lhs, const Entity& rhs)
{
        return !(lhs == rhs);
}
