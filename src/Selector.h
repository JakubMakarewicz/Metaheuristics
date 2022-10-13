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
    virtual std::vector<Specimen> RunSelection(std::vector<Specimen>& population) = 0;
};

class RouletteSelector: public Selector {
public:
    std::vector<Specimen> RunSelection(std::vector<Specimen>& population) override;
private:
    double NormalizeFitness(std::vector<Specimen>& population);
};



class TournamentSelector: public Selector {

};

#endif //METAHEURISTICS_SELECTOR_H
