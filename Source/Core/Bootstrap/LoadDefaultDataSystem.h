#pragma once

#ifndef __LOADDEFAULTDATASYSTEM__H__
#    define __LOADDEFAULTDATASYSTEM__H__

#    ifndef _HAS_CHAR8_T
#        define _HAS_CHAR8_T 0
#    endif

#    define JSON_NO_CHAR8_T

#    include "../External/json.hpp"
#include  "../EntityType.h"
using json = nlohmann::json;

#    include <fstream>
#    include <axmol.h>
#    include <string>
#    include <iostream>
#    include <filesystem>

#    include "../Data/EntityBaseData.h"
#	 include "../Data/EntityBaseStorage.h"
USING_NS_AX;

class LoadDefaultDataSystem
{
public:
    LoadDefaultDataSystem();
    ~LoadDefaultDataSystem();
    
    void writeData();

private:
    EntityBaseData baseData;
    json data;
    EntityBaseStorage EBS = EntityBaseStorage::getInstance();
	EntityType entityType;
};

#endif