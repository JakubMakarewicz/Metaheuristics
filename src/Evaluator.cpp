//
// Created by kuba on 10/7/22.
//

#include "Evaluator.h"
double Evaluator::EvaluateSpecimen(Specimen &specimen) {
    double knapsackValue=0;
    double tspCost=0;
    double currentWeight=0;
    for (int i=0; i<specimen.nodeGenome.size();i++){
        std::tuple<double,double> nodeWeightAndProfit = this->GetItemsWeightAndProfitForNode(specimen, i);
        currentWeight += std::get<0>(nodeWeightAndProfit);
        knapsackValue += std::get<1>(nodeWeightAndProfit);
        double distance = this->data.nodes.at(specimen.nodeGenome.at(i)).getDistance(data.nodes.at(specimen.nodeGenome.at((i+1)%specimen.nodeGenome.size())));
        tspCost += distance/(this->data.maxSpeed - currentWeight*this->data.velocityConst);
    }
    specimen.fitness = knapsackValue - tspCost;
    return knapsackValue - tspCost;
}

std::tuple<double,double> Evaluator::GetItemsWeightAndProfitForNode(const Specimen &specimen, int node) {
    std::tuple<double,double> result(0,0);
    if (this->data.itemsAtNodeMap.find(node) != this->data.itemsAtNodeMap.end()){
        std::vector<Item> itemsAtNode = this->data.itemsAtNodeMap.at(node);
        for (auto & i : itemsAtNode){
            if (specimen.itemGenome.at(i.index)){
                std::get<0>(result) += i.weight;
                std::get<1>(result) += i.profit;
            }
        }
    }
    return result;
}
