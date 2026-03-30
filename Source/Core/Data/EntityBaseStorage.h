#pragma once
#include <vector>
#include <fstream>
#include "../EntityType.h"
#include<axmol.h>
#include "EntityBaseData.h"
#include "../External/json.hpp"

#ifndef __ENTITYBASESTORAGE_H__
#define __ENTITYBASESTORAGE_H__


class EntityBaseStorage
{
private:
    std::vector<EntityType> allTypes;  // take All EntityType values and store them in a vector
    std::vector<EntityBaseData> allBaseData;  // Store base data for each entity type

public:
    EntityBaseStorage();
    ~EntityBaseStorage();
    static EntityBaseStorage& getInstance();  // Method to get the singleton instance of EntityBaseStorage
    void setData(EntityType e , EntityBaseData v);  // Method to set up the base data for each entity type
    void showData();  // Method to show the base data for each entity type (for testing purposes)
};
#endif  // __ENTITYBASESTORAGE_H__