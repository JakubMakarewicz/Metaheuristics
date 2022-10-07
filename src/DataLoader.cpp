//
// Created by kuba on 10/6/22.
//

#include <fstream>
#include <sstream>
#include "DataLoader.h"

bool DataLoader::loadData(const std::string& filePath) {
    std::fstream dataFile;
    dataFile.open(filePath, std::ios::in);
    if (dataFile.is_open()){
        std::string line;
        getline(dataFile, line);
        this->data.problemName = this->splitString(line, '\t')[1];
        getline(dataFile, line);
        this->data.knapsackDataType = this->splitString(line, '\t')[1];
        getline(dataFile, line);
        this->data.nodeCount = std::stoi(this->splitString(line, '\t')[1]);
        getline(dataFile, line);
        this->data.itemsCount = std::stoi(this->splitString(line, '\t')[1]);
        getline(dataFile, line);
        this->data.knapsackCapacity = std::stoi(this->splitString(line, '\t')[1]);
        getline(dataFile, line);
        this->data.minSpeed = std::stod(this->splitString(line, '\t')[1]);
        getline(dataFile, line);
        this->data.maxSpeed = std::stod(this->splitString(line, '\t')[1]);
        getline(dataFile, line);
        this->data.rentingRatio = std::stod(this->splitString(line, '\t')[1]);
        getline(dataFile, line);
        this->data.edgeWeightType = this->splitString(line, '\t')[1];
        getline(dataFile, line);
//        read nodes
        while(getline(dataFile, line) && line != "ITEMS SECTION\t(INDEX, PROFIT, WEIGHT, ASSIGNED NODE NUMBER): "){
            Node node{};
            std::vector<std::string> splitLine = this->splitString(line, '\t');
            node.index=std::stoi(splitLine[0])-1;
            node.x = std::stod(splitLine[1]);
            node.y = std::stod(splitLine[2]);
            this->data.nodes.push_back(node);
        }
//        read items
        while(getline(dataFile, line)){
            Item item{};
            std::vector<std::string> splitLine = this->splitString(line, '\t');
            item.index=std::stoi(splitLine[0])-1;
            item.profit=std::stod(splitLine[1]);
            item.weight=std::stod(splitLine[2]);
            item.node=std::stoi(splitLine[3]);
            this->data.items.push_back(item);
            if (this->data.itemsAtNodeMap.find(item.node) != this->data.itemsAtNodeMap.end()) {
                this->data.itemsAtNodeMap.at(item.node).push_back(item);
            }
            else {
                this->data.itemsAtNodeMap.insert({item.node, std::vector<Item>{item}});
            }
        }

//      initialize adjecency map
        for (int i = 0; i<this->data.nodes.size(); i++){
            for (int j = 0; j<this->data.nodes.size(); j++) {
                this->data.nodeAdjacencyMatrix[i][j] = this->data.nodes[i].getDistance(this->data.nodes[j]);
            }
        }

        this->data.velocityConst = (this->data.maxSpeed - this->data.minSpeed)/this->data.knapsackCapacity;

        dataFile.close();
    }
    return false;
}
std::vector<std::string> DataLoader::splitString(const std::string& stringToSplit, char delim) {
    std::string segment;
    std::vector<std::string> seglist;
    std::stringstream stream = std::stringstream(stringToSplit);
    while(std::getline(stream, segment, delim))
    {
        seglist.push_back(segment);
    }
    return seglist;
}