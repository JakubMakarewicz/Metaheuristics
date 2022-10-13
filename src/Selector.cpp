//
// Created by kuba on 10/7/22.
//

#include "Selector.h"
std::vector<Specimen> RouletteSelector::RunSelection(std::vector<Specimen>& population) {
    Fenwick_tree<double> fenwickTree{};
    double sum;

    sum = this->NormalizeFitness(population);

    for(auto & i : population){
        fenwickTree.push((i.normalizedFitness)/sum);
    }

    std::default_random_engine generator;
    std::uniform_real_distribution distribution;
    std::vector<Specimen> newGeneration;
    for (int i=0; i<population.size();i++){
        newGeneration.push_back(population.at(fenwickTree.upper_bound(distribution(generator))));
    }

    return newGeneration;
}

double RouletteSelector::NormalizeFitness(std::vector<Specimen> &population) {
    double minFitness=std::numeric_limits<double>::infinity();
    double sum=0.0;
    for (auto & i : population){
        if (i.fitness < minFitness)
            minFitness = i.fitness;
    }
    if (minFitness<0){
        minFitness *=-1;
        for (auto & i : population){
            i.normalizedFitness = i.fitness + minFitness;
            sum+=i.normalizedFitness;
        }
    }
    return sum;
}
