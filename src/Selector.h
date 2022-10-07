//
// Created by kuba on 10/7/22.
//

#ifndef METAHEURISTICS_SELECTOR_H
#define METAHEURISTICS_SELECTOR_H

#include <cstddef>
#include "Specimen.h"

enum SelectorEnum{
    ROULETTE,
    TOURNAMENT
};
template<std::size_t N, std::size_t I, std::size_t P>
class TournamentSelector;
template<std::size_t N, std::size_t I, std::size_t P>
class RouletteSelector;

template<std::size_t N, std::size_t I, std::size_t P>
class Selector {
    virtual std::array<Specimen<N,I>, P> RunSelection(std::array<Specimen<N,I>, P>& population) = 0;
    Selector<N,I,P> GenerateSelector(SelectorEnum selectorEnum){
        switch (selectorEnum) {
            case ROULETTE: {
                RouletteSelector<N,I,P> selector{};
                return selector;
            }
            case TOURNAMENT: {
                TournamentSelector<N,I,P> selector{};
                return selector;
            }
        }
    }
};

template<std::size_t N, std::size_t I, std::size_t P>
class RouletteSelector: public Selector<N,I,P> {

};
template<std::size_t N, std::size_t I, std::size_t P>
class TournamentSelector: public Selector<N,I,P> {

};

#endif //METAHEURISTICS_SELECTOR_H
