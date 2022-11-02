//
// Created by kuba on 10/6/22.
//

#ifndef METAHEURISTICS_DATALOADER_H
#define METAHEURISTICS_DATALOADER_H


#include "DataStructure.h"
#include "Config.h"

class DataLoader {
public://
    DataStructure data;
    Config config;
    bool loadData(const std::string& filePath);
    bool loadConfig(const std::string& filePath);
private:
    std::vector<std::string> splitString(const std::string& stringToSplit, char delim);
};


#endif //METAHEURISTICS_DATALOADER_H
