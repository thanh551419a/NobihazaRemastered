#pragma once
#include <vector>
#include <cstdint>
#ifndef __COMPONENT_POOL_H__
#    include <algorithm>
#    define __COMPONENT_POOL_H__

using EntityID = uint32_t;

template <typename T>
class ComponentPool
{
private:
    std::vector<T> Components;
    std::vector<EntityID> Entities;

    static const int MAX_ENTITIES = 10000;

    int lookup[MAX_ENTITIES];

public:
    ComponentPool()
    {
        for (int i = 0; i < MAX_ENTITIES; i++)
        {
            lookup[i] = -1;
        }
    }

    void add(EntityID entity, T component)
    {
        Components.push_back(component);

        Entities.push_back(entity);

        lookup[entity] = Components.size() - 1;
    }

    void remove(EntityID entity)
    {
        int removeIndex = lookup[entity];

        int lastIndex = Components.size() - 1;

        EntityID lastEntity = Entities[lastIndex];

        std::swap(Components[removeIndex], Components[lastIndex]);

        std::swap(Entities[removeIndex], Entities[lastIndex]);

        lookup[lastEntity] = removeIndex;

        Components.pop_back();

        Entities.pop_back();

        lookup[entity] = -1;
    }

    T& get(EntityID entity) { return Components[lookup[entity]]; }

    bool has(EntityID entity) { return lookup[entity] != -1; }

    int size() { return Components.size(); }

    EntityID getEntity(int index) { return Entities[index]; }

    T& getByIndex(int index) { return Components[index]; }

    void clear()
    {
        Components.clear();
        Entities.clear();

        for (int i = 0; i < MAX_ENTITIES; i++)
        {
            lookup[i] = -1;
        }
    }
};

#endif  // !__COMPONENT_POOL_H__
