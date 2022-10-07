//
// Created by kuba on 10/7/22.
//

#ifndef METAHEURISTICS_EVALUATOR_H
#define METAHEURISTICS_EVALUATOR_H

#include <cstddef>
#include "DataStructure.h"
#include "Specimen.h"

template<std::size_t N, std::size_t I>
class Evaluator {
public:
    DataStructure data;
    double EvaluateSpecimen(const Specimen<N,I>& specimen);
private:
    std::tuple<double, double> GetItemsWeightAndProfitForNode(const Specimen<N,I>& specimen, int node);
};

template<std::size_t N, std::size_t I>
double Evaluator<N, I>::EvaluateSpecimen(const Specimen<N, I> &specimen) {
    double knapsackValue=0;
    double tspCost=0;
    double currentWeight=0;
    for (int i=0; i<N;i++){
        std::tuple<double,double> nodeWeightAndProfit = this->GetItemsWeightAndProfitForNode(specimen, i);
        currentWeight += std::get<0>(nodeWeightAndProfit);
        knapsackValue += std::get<1>(nodeWeightAndProfit);
        double distance = this->data.nodes.at(specimen.nodeGenome[i]).getDistance(data.nodes.at(specimen.nodeGenome[(i+1)%N]));
        tspCost += distance/(this->data.maxSpeed - currentWeight*this->data.velocityConst);
    }
    return knapsackValue - tspCost;
}

template<std::size_t N, std::size_t I>
std::tuple<double,double> Evaluator<N, I>::GetItemsWeightAndProfitForNode(const Specimen<N, I> &specimen, int node) {
    std::tuple<double,double> result(0,0);
    if (this->data.itemsAtNodeMap.find(node) != this->data.itemsAtNodeMap.end()){
        std::vector<Item> itemsAtNode = this->data.itemsAtNodeMap.at(node);
        for (auto & i : itemsAtNode){
            if (specimen.itemGenome.test(i.index)){
                std::get<0>(result) += i.weight;
                std::get<1>(result) += i.profit;
            }
        }
    }
    return result;
}


#endif //METAHEURISTICS_EVALUATOR_H
