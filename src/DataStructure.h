//
// Created by kuba on 10/6/22.
//

#ifndef METAHEURISTICS_DATASTRUCTURE_H
#define METAHEURISTICS_DATASTRUCTURE_H

#include <string>
#include <vector>
#include <map>
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

    double velocityConst;
    std::vector<std::vector<double>> nodeAdjacencyMatrix;
    std::map<int, std::vector<Item>> itemsAtNodeMap;
    std::vector<Item> itemsSorted;
private:
};


#endif //METAHEURISTICS_DATASTRUCTURE_H
