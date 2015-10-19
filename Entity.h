#ifndef ENTITY_H
#define ENTITY_H

#include <map>

class EntitySeed
{
    unsigned count_ = 1;
    friend class Entity;
};

class Entity
{
    public:
        Entity();
        Entity(EntitySeed& seed);
        Entity(const Entity&) = default;
        ~Entity() = default;

        Entity& operator=(const Entity&) = default;

        bool is_null();

        static Entity Null;

    private:
        unsigned id_;

    friend bool operator==(const Entity& lhs, const Entity& rhs);
    friend bool operator!=(const Entity& lhs, const Entity& rhs);
};

#endif // ENTITY_H
