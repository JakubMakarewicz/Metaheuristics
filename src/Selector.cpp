//
// Created by kuba on 10/7/22.
//

#include "Selector.h"
#include "RandomGenerators.h"
std::unique_ptr<std::vector<Specimen*>> RouletteSelector::RunSelection(std::vector<Specimen*>& population) {
    Fenwick_tree<double> fenwickTree{};
    double sum;

    sum = this->NormalizeFitness(population);
    double sum_a_i = 0;
    for(auto & i : population){
        fenwickTree.push((i->normalizedFitness)/sum);
        sum_a_i += (i->normalizedFitness) / sum;
    }

    rand->rouletteDist = new std::uniform_real_distribution<>(0, sum_a_i);
    //std::random_device rd;
    //std::mt19937_64 mt(rd());

    auto newGeneration=std::make_unique<std::vector<Specimen*>>();
    for (int i=0; i<population.size();i++){
        //Specimen newSpecimen(population.at(fenwickTree.upper_bound(distribution(generator))));
        int index = fenwickTree.upper_bound((*(rand->RandomGenerators::rouletteDist))(*rand->mt));
        if (index == population.size())
            index -=1; //TODO:XD!
        newGeneration->push_back(new Specimen(*population.at(index)));

    }
    for (int i = 0; i < population.size();i++) {
        delete population.at(i);
    }
    return newGeneration;
}
//o
double RouletteSelector::NormalizeFitness(std::vector<Specimen*> &population) {
    double minFitness=std::numeric_limits<double>::infinity();
    double sum=0.0;
    for (int i = 0; i<population.size(); i++){
        if (population.at(i)->fitness < minFitness)
            minFitness = population.at(i)->fitness;
    }
    bool wasNegative = false;
    if (minFitness < 0) {
        minFitness *= -1;
        wasNegative = true;
    }
    for (int i = 0; i < population.size(); i++) {
        if (wasNegative)
            population.at(i)->normalizedFitness = population.at(i)->fitness + minFitness;
        else population.at(i)->normalizedFitness = population.at(i)->fitness - minFitness;
        sum += population.at(i)->normalizedFitness;
    }
    return sum;
}

RouletteSelector::RouletteSelector(RandomGenerators &rand) : Selector(rand) {}

std::unique_ptr<std::vector<Specimen*>> TournamentSelector::RunSelection(std::vector<Specimen*>& population){
    auto newGeneration = std::make_unique<std::vector<Specimen*>>();
    for (int i = 0;i < population.size(); i++) {
        std::vector<Specimen*> tournamentSpecimens;
        std::sample(
            population.begin(),
            population.end(),
            std::back_inserter(tournamentSpecimens),
            this->tournamentSize,
            std::mt19937(std::random_device()())
        );
        newGeneration->push_back(new Specimen((*this->RunSingleTournament(tournamentSpecimens))));
        
//        newGeneration->push_back(this->RunSingleTournament(tournamentSpecimens));
    }
    for (int i = 0; i < population.size();i++) {
        delete population.at(i);
    }
    return newGeneration;
}

Specimen* TournamentSelector::RunSingleTournament(std::vector<Specimen*>& population){
    double bestScore = INT_MIN;
    int bestIndex = 0;
    for (int i = 0;i < population.size(); i++) {
        if (population.at(i)->fitness > bestScore) {
            bestScore = population.at(i)->fitness;
            bestIndex = i;
        }
    }
    return population.at(bestIndex);
}

Selector* Selector::GenerateSelector(std::string selectorName, int tournamentSize, RandomGenerators& rand)
{
    if (selectorName == "ROULETTE") {
        return new RouletteSelector(rand);
    }
    else if (selectorName == "TOURNAMENT") {
        return new TournamentSelector(rand, tournamentSize);
    }
}

Selector::Selector(RandomGenerators& rand) : rand(&rand) {}
