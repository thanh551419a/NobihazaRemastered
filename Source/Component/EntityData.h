#pragma once
#include<axmol.h>
#include "./Core/CoreTypes.h"
class EntityData
{
    int Hp;
    bool isDead;
    ax::Vec2 Position;
    ax::Vec2 Direction;
    EntityType EntityType;
};
