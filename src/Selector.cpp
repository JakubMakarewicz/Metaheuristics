//
// Created by kuba on 10/7/22.
//

#include "Selector.h"
std::vector<Specimen> RouletteSelector::RunSelection(std::vector<Specimen>& population, Evaluator& evaluator) {
    Fenwick_tree<double> fenwickTree{};
    double sum=0;
    for (int i=0;i<population.size();i++){
        sum+=evaluator.EvaluateSpecimen(population.at(i));
    }
    for(int i =0; i<population.size(); i++){
//        if (i==P-1)
//            fenwickTree.push(1);
//        else
        auto val =(population[i].fitness)/sum;
        fenwickTree.push((population.at(i).fitness)/sum);
    }

    std::default_random_engine generator;
    std::uniform_real_distribution distribution;
    std::vector<Specimen> newGeneration;
    for (int i=0; i<population.size();i++){
        newGeneration.push_back(population.at(fenwickTree.upper_bound(distribution(generator))));
    }

    return newGeneration;
}