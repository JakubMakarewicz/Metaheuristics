//
// Created by kuba on 10/6/22.
//

#include <fstream>
#include <sstream>
#include <algorithm>
#include "DataLoader.h"

bool DataLoader::loadData(const std::string& filePath) {
    std::fstream dataFile;
    dataFile.open(filePath, std::ios::in);
    if (dataFile.is_open()){
        std::string line;
        getline(dataFile, line);
        this->data.problemName = this->splitString(line, '\t')[1];
        getline(dataFile, line);
//        this->data.knapsackDataType = this->splitString(line, '\t')[1];
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
        while(getline(dataFile, line) && (line.find("ITEMS SECTION") == std::string::npos)){
            Node node{};
            std::vector<std::string> splitLine = this->splitString(line, '\t');
            node.index=std::stoi(splitLine[0])-1;
            node.x = std::stod(splitLine[1]);
            node.y = std::stod(splitLine[2]);
            this->data.nodes.push_back(node);
        }
//        read items
        while(getline(dataFile, line)){
            std::vector<std::string> splitLine = this->splitString(line, '\t');
            Item item{
            std::stoi(splitLine[0])-1,
            std::stod(splitLine[1]),
            std::stod(splitLine[2]),
            std::stoi(splitLine[3])-1};
            this->data.items.push_back(item);
            if (this->data.itemsAtNodeMap.find(item.node) != this->data.itemsAtNodeMap.end()) {
                this->data.itemsAtNodeMap.at(item.node).push_back(item);
            }
            else {
                this->data.itemsAtNodeMap.insert({item.node, std::vector<Item>{item}});//
            }
        }

//      initialize adjecency map
        for (int i = 0; i<this->data.nodes.size(); i++){
            this->data.nodeAdjacencyMatrix.emplace_back();
            for (int j = 0; j<this->data.nodes.size(); j++) {
                double dist = this->data.nodes.at(i).getDistance(this->data.nodes.at(j));
                this->data.nodeAdjacencyMatrix.at(i).push_back(dist);
            }
        }

        this->data.velocityConst = (this->data.maxSpeed - this->data.minSpeed)/this->data.knapsackCapacity;

        this->data.itemsSorted=this->data.items;
        std::sort(this->data.itemsSorted.begin(), this->data.itemsSorted.end());


        dataFile.close();
        return true;
    }
    return false;
}
bool DataLoader::loadConfig(const std::string& filePath)
{
    std::fstream dataFile;
    dataFile.open(filePath, std::ios::in);
    if (dataFile.is_open()) {
        std::string line;
        getline(dataFile, line);
        this->config.crossoverProbability = std::stod(this->splitString(line, ';')[1]);
        getline(dataFile, line);
        this->config.specimenNodeGenomeMutationProbability = std::stod(this->splitString(line, ';')[1]);
        getline(dataFile, line);
        this->config.nodeMutationProbability = std::stod(this->splitString(line, ';')[1]);
        getline(dataFile, line);
        this->config.itemMutationProbability = std::stod(this->splitString(line, ';')[1]);
        getline(dataFile, line);
        this->config.annealingRatio = std::stod(this->splitString(line, ';')[1]);
        getline(dataFile, line);
        this->config.startingTemperature = std::stod(this->splitString(line, ';')[1]);
        getline(dataFile, line);
        this->config.targetTemperature = std::stod(this->splitString(line, ';')[1]);
        getline(dataFile, line);
        this->config.mutateKnapsack = std::stoi(this->splitString(line, ';')[1]);
        getline(dataFile, line);
        this->config.generateGreedyKnapsackPostCross = std::stoi(this->splitString(line, ';')[1]);
        getline(dataFile, line);
        this->config.mutateOnlyOnce = std::stoi(this->splitString(line, ';')[1]);
        getline(dataFile, line);
        this->config.populationSize = std::stoi(this->splitString(line, ';')[1]);
        getline(dataFile, line);
        this->config.generationsCount = std::stoi(this->splitString(line, ';')[1]);
        getline(dataFile, line);
        this->config.tournamentBatchSize = std::stoi(this->splitString(line, ';')[1]);
        getline(dataFile, line);
        this->config.tabooSize = std::stoi(this->splitString(line, ';')[1]);
        getline(dataFile, line);
        this->config.selector = this->splitString(line, ';')[1];
        getline(dataFile, line);
        this->config.crossoverer = this->splitString(line, ';')[1];
        getline(dataFile, line);
        this->config.mutator = this->splitString(line, ';')[1];
        getline(dataFile, line);
        this->config.factory = this->splitString(line, ';')[1];
        getline(dataFile, line);
        this->config.dataFilePath = this->splitString(line, ';')[1];
        getline(dataFile, line);
        this->config.algorithm = this->splitString(line, ';')[1];
        getline(dataFile, line);
        this->config.tries = std::stoi(this->splitString(line, ';')[1]);
        getline(dataFile, line);
        this->config.outputFilePath = this->splitString(line, ';')[1];
        getline(dataFile, line);
        this->config.outputFilePath2 = this->splitString(line, ';')[1];
        dataFile.close();
        return true;
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