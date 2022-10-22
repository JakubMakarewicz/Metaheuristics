//
// Created by kuba on 10/7/22.
//

#ifndef METAHEURISTICS_SELECTOR_H
#define METAHEURISTICS_SELECTOR_H

#include <cstddef>
#include <random>
#include "Specimen.h"
#include "../utils/fenwick_tree.h"
#include "Evaluator.h"
#include "RandomGenerators.h"

enum SelectorEnum{
    ROULETTE,
    TOURNAMENT
};
class TournamentSelector;
class RouletteSelector;

class Selector {
public:
    RandomGenerators* rand;

    explicit Selector(RandomGenerators& rand);

    virtual std::unique_ptr<std::vector<Specimen*>> RunSelection(std::vector<Specimen*>& population) = 0;

    static Selector* GenerateSelector(std::string selectorName, int tournamentSize, RandomGenerators& rand);

};
//
class RouletteSelector: public Selector {
public:
    explicit RouletteSelector(RandomGenerators &rand);

    std::unique_ptr<std::vector<Specimen*>> RunSelection(std::vector<Specimen*>& population) override;
private:
    double NormalizeFitness(std::vector<Specimen*>& population);
};



class TournamentSelector: public Selector {
public:
    int tournamentSize;

    TournamentSelector(RandomGenerators& rand, int tournamentSize): Selector(rand) { this->tournamentSize = tournamentSize; }
    std::unique_ptr<std::vector<Specimen*>> RunSelection(std::vector<Specimen*>& population) override;
private:
    Specimen* RunSingleTournament(std::vector<Specimen*>& population);
};

#endif //METAHEURISTICS_SELECTOR_H
