//
// Created by kuba on 10/7/22.
//

#include "Selector.h"
#include "RandomGenerators.h"
std::vector<Specimen*> RouletteSelector::RunSelection(std::vector<Specimen*>& population) {
    Fenwick_tree<double> fenwickTree{};
    double sum;

    sum = this->NormalizeFitness(population);
    double sum_a_i = 0;
    for(auto & i : population){
        fenwickTree.push((i->normalizedFitness)/sum);
        sum_a_i += (i->normalizedFitness) / sum;
    }

    RandomGenerators::rouletteDist = new std::uniform_real_distribution<>(0, sum_a_i);


    std::vector<Specimen*> newGeneration;
    for (int i=0; i<population.size();i++){
        //Specimen newSpecimen(population.at(fenwickTree.upper_bound(distribution(generator))));
        newGeneration.push_back(population.at(fenwickTree.upper_bound((*RandomGenerators::rouletteDist)(RandomGenerators::mt))));
    }

    return newGeneration;
}

double RouletteSelector::NormalizeFitness(std::vector<Specimen*> &population) {
    double minFitness=std::numeric_limits<double>::infinity();
    double sum=0.0;
    for (auto & i : population){
        if (i->fitness < minFitness)
            minFitness = i->fitness;
    }
    if (minFitness < 0) {
        minFitness *= -1;
    }
    for (auto & i : population){
        if (minFitness < 0)
            i->normalizedFitness = i->fitness + minFitness;
        else i->normalizedFitness = i->fitness - minFitness;
        sum += i->normalizedFitness;
    }
    return sum;
}

std::vector<Specimen*> TournamentSelector::RunSelection(std::vector<Specimen*>& population){   
    std::vector<Specimen*> newGeneration;
    for (int i = 0;i < population.size(); i++) {
        std::vector<Specimen*> tournamentSpecimens;
        std::sample(
            population.begin(),
            population.end(),
            std::back_inserter(tournamentSpecimens),
            this->tournamentSize,
            RandomGenerators::tournamentEngine
        );
        newGeneration.push_back(this->RunSingleTournament(tournamentSpecimens));
    }
    return newGeneration;
}

Specimen* TournamentSelector::RunSingleTournament(std::vector<Specimen*>& population){
    double bestScore = std::numeric_limits<double>::min();
    int bestIndex = 0;
    for (int i = 0;i < population.size(); i++) {
        if (population.at(i)->fitness > bestScore) {
            bestScore = population.at(i)->fitness;
            bestIndex = i;
        }
    }
    return population.at(bestIndex);
}

Selector* Selector::GenerateSelector(std::string selectorName, int tournamentSize)
{
    if (selectorName == "ROULETTE") {
        return new RouletteSelector;
    }
    else if (selectorName == "TOURNAMENT") {
        return new TournamentSelector(tournamentSize);
    }
}