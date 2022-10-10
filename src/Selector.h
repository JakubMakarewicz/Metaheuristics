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
    virtual std::vector<Specimen> RunSelection(std::vector<Specimen>& population, Evaluator& evaluator) = 0;
//    Selector<N,I,P> GenerateSelector(SelectorEnum selectorEnum){
//        switch (selectorEnum) {
//            case ROULETTE: {
//                RouletteSelector<N,I,P> selector{};
//                return selector;
//            }
//            case TOURNAMENT: {
//                TournamentSelector<N,I,P> selector{};
//                return selector;
//            }
//        }
//    }
};

class RouletteSelector: public Selector {
public:
    std::vector<Specimen> RunSelection(std::vector<Specimen>& population, Evaluator& evaluator) override;
private:
};



class TournamentSelector: public Selector {

};

#endif //METAHEURISTICS_SELECTOR_H
