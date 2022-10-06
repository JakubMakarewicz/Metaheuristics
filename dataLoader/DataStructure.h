//
// Created by kuba on 10/6/22.
//

#ifndef METAHEURISTICS_DATASTRUCTURE_H
#define METAHEURISTICS_DATASTRUCTURE_H

#include <string>
#include <vector>
#include "Node.h"
#include "Item.h"

class DataStructure {
public:
    std::string problemName;
    std::string knapsackDataType;
    int nodeCount;
    int itemsCount;
    int knapsackCapacity;
    double minSpeed;
    double maxSpeed;
    double rentingRatio;
    std::string edgeWeightType;
    std::vector<Node> nodes;
    std::vector<Item> items;
};


#endif //METAHEURISTICS_DATASTRUCTURE_H
