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

enum SelectorEnum{
    ROULETTE,
    TOURNAMENT
};
class TournamentSelector;
class RouletteSelector;

class Selector {
public:
    virtual std::vector<Specimen> RunSelection(std::vector<Specimen>& population) {}

    static Selector& GenerateSelector(std::string selectorName, int tournamentSize=0) {
        if (selectorName == "ROULETTE"){
            RouletteSelector selector;
            return selector;
        }
        else if (selectorName == "TOURNAMENT") {
            TournamentSelector selector(tournamentSize);
            return selector;
        }
    }

};

class RouletteSelector: public Selector {
public:
    std::vector<Specimen> RunSelection(std::vector<Specimen>& population) override;
private:
    double NormalizeFitness(std::vector<Specimen>& population);
};



class TournamentSelector: public Selector {
public:
    int tournamentSize;

    TournamentSelector(int tournamentSize) { this->tournamentSize = tournamentSize; }
    std::vector<Specimen> RunSelection(std::vector<Specimen>& population) override;
private:
    Specimen& RunSingleTournament(std::vector<Specimen>& population);
};

#endif //METAHEURISTICS_SELECTOR_H
