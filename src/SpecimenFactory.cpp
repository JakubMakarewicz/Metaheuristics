//
// Created by kuba on 10/13/22.
//

#include "SpecimenFactory.h"
#include<cstdlib>
#include <random>
#include "RandomGenerators.h"
void RandomSpecimenFactory::InitializeSpecimen(Specimen &specimen) {
    specimen.nodeGenome.clear();
    for (int i = 0; i<this->data.nodeCount; i++){
        specimen.nodeGenome.push_back(i);
    }
    std::shuffle(specimen.nodeGenome.begin(), specimen.nodeGenome.end(), std::mt19937_64(std::random_device()()));

    this->GenerateGreedyItems(specimen);
}

void GreedySpecimenFactory::InitializeSpecimen(Specimen &specimen) {
    specimen.nodeGenome.clear();
    //std::random_device rd;
    //std::mt19937_64 mt(rd());
    int start = (*rand->distStart)(*rand->mt);
    std::vector<bool> availableNodes;
    for (int i = 0; i<this->data.nodeCount; i++)
        availableNodes.push_back(true);

    specimen.nodeGenome.push_back(start);
    availableNodes.at(start).flip();
    while (specimen.nodeGenome.size()<this->data.nodeCount){
        int next = this->GetClosest(specimen.nodeGenome.back(), availableNodes);
        specimen.nodeGenome.push_back(next);
        availableNodes.at(next).flip();
    }
    this->GenerateGreedyItems(specimen);
//    for (int i = 0; i<this->data)
}

int SpecimenFactory::GetClosest(int currentNode, std::vector<bool>& availableNodes) const{
    double minVal=std::numeric_limits<double>::infinity();
    int minNode=0;
    for (int i=0; i<this->data.nodeCount; i++){
        if (availableNodes.at(i)) {
            double currentDist = this->data.nodeAdjacencyMatrix[currentNode][i];
            if (currentDist < minVal){
                minNode = i;
                minVal= currentDist;
            }
        }
    }
    return minNode;
}

void SpecimenFactory::GenerateGreedyItems(Specimen& specimen){
    specimen.ClearKnapsack();
    std::vector<Item> itemsSorted{this->data.items};
    double currentDistance = 0;
    for (int i = specimen.nodeGenome.size()-1; i>=0; i--){
        currentDistance += data.nodeAdjacencyMatrix.at(specimen.nodeGenome.at((i+1)%data.nodeCount)).at(specimen.nodeGenome.at(i));
        if (this->data.itemsAtNodeMap.find(specimen.nodeGenome.at(i)) != this->data.itemsAtNodeMap.end()){
            std::vector<Item> itemsAtNode = this->data.itemsAtNodeMap.at(specimen.nodeGenome.at(i));
            for (int i = 0; i< itemsAtNode.size(); i++){
                itemsSorted.at(itemsAtNode.at(i).index).profitMargin = itemsAtNode.at(i).profit / (itemsAtNode.at(i).weight * currentDistance);
            }
        }
    }
    std::sort(itemsSorted.begin(), itemsSorted.end());
    for (int i = itemsSorted.size() - 1; i >= 0; i--) {
        specimen.PickupItem(this->data.items.at(itemsSorted.at(i).index), this->data);
    }
}
//
SpecimenFactory* SpecimenFactory::GenerateSpecimenFactory(std::string specimenFactoryName, DataStructure& data, RandomGenerators& rand)
{
    if (specimenFactoryName == "RANDOM") {
        return new RandomSpecimenFactory(data,rand);
    }
    else if (specimenFactoryName == "GREEDY") {
        return new GreedySpecimenFactory(data,rand);
    }
}
