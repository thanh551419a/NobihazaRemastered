#include "EntityBaseStorage.h"

#include<iostream>
EntityBaseStorage& EntityBaseStorage::getInstance() {
	static EntityBaseStorage instance;  // Guaranteed to be destroyed and instantiated on first use
	return instance;
}
EntityBaseStorage::EntityBaseStorage() {// setup size of vectors
    for (int i = 0; i < (int)EntityType::COUNT + 1; i++)
    {
        allTypes.push_back((EntityType)i);  // Create a vector of all EntityType values
    };
    allBaseData.resize(allTypes.size());  // Resize the allBaseData vector to match the number of entity types
}

EntityBaseStorage::~EntityBaseStorage() {
	// Destructor code here
	AXLOG("EntityBaseStorage Destructor");
}
void EntityBaseStorage::setData(EntityType e , EntityBaseData v) {
    for (int i = 0 ; i < allTypes.size(); i++)
	{
		if (allTypes[i] == e) {
			allBaseData[i] = v;  // Set the base data for the specified entity type
			break;
		}
    }
}
void EntityBaseStorage::showData() {
	for (int i = 0 ; i < allTypes.size(); i++)
	{
		std::cout << "Entity Type: " << (int)allTypes[i] << std::endl;
		std::cout << "Max HP: " << allBaseData[i].maxHp << std::endl;
		std::cout << "Armor: " << allBaseData[i].arrmor << std::endl;
		std::cout << "Speed: " << allBaseData[i].speed << std::endl;
		std::cout << "Damage: " << allBaseData[i].damage << std::endl;
		std::cout << "-----------------------------" << std::endl;
	}
}



