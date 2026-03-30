#include "LoadDefaultDataSystem.h"

LoadDefaultDataSystem::LoadDefaultDataSystem() {
	// Constructor code here
    std::ifstream file("../Source/Core/Data/EntityAttribute.json");
    //std::cout << std::filesystem::current_path() << std::endl;
	if (!file.is_open()) {
		AXLOG("Failed to open EntityAttribute.json");
		return;
    }// open file json

	
    file >> data;
    std::cout << data;
    
	baseData.maxHp = data["componentDefaults"]["Health"]["maxHP"].get<int>();
    baseData.arrmor = data["componentDefaults"]["Armor"]["value"].get<int>();
    baseData.speed  = data["componentDefaults"]["Movement"]["speed"].get<int>();
    baseData.damage = data["componentDefaults"]["Attack"]["damage"].get<int>();
	
	writeData();
}

void LoadDefaultDataSystem::writeData() {
    for (int i = 0 ; i < (int)EntityType::COUNT; i++)
	{
		entityType = (EntityType)i;
		EBS.setData(entityType, baseData);  // Set the base data for each entity type in the storage
    }

}
LoadDefaultDataSystem::~LoadDefaultDataSystem()
{
	// Destructor code here
	AXLOG("LoadDefaultDataSystem Destructor");
}