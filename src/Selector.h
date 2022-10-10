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
template<std::size_t N, std::size_t I, std::size_t P>
class TournamentSelector;
template<std::size_t N, std::size_t I, std::size_t P>
class RouletteSelector;

template<std::size_t N, std::size_t I, std::size_t P>
class Selector {
    virtual std::array<Specimen<N,I>, P> RunSelection(std::array<Specimen<N,I>, P>& population, Evaluator<N,I>& evaluator) = 0;
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

template<std::size_t N, std::size_t I, std::size_t P>
class RouletteSelector: public Selector<N,I,P> {
public:
    std::array<Specimen<N,I>, P> RunSelection(std::array<Specimen<N,I>, P>& population, Evaluator<N,I>& evaluator);
private:
    Specimen<N,I> SingleRoulette();
};

template<std::size_t N, std::size_t I, std::size_t P>
std::array<Specimen<N, I>, P> RouletteSelector<N, I, P>::RunSelection(std::array<Specimen<N, I>, P> &population, Evaluator<N,I>& evaluator) {
    Fenwick_tree<double> fenwickTree{};
    double sum=0;
    for (int i=0;i<P;i++){
        sum+=evaluator.EvaluateSpecimen(population[i]);
    }
    for(int i =0; i<P; i++){
//        if (i==P-1)
//            fenwickTree.push(1);
//        else
        auto val =(population[i].fitness)/sum;
            fenwickTree.push((population[i].fitness)/sum);
    }

    std::default_random_engine generator;
    std::uniform_real_distribution distribution;
    std::array<Specimen<N, I>, P> newGeneration;
    for (int i=0; i<P;i++){
        newGeneration[i] = population[fenwickTree.upper_bound(distribution(generator))];
    }

    return newGeneration;
}

template<std::size_t N, std::size_t I, std::size_t P>
class TournamentSelector: public Selector<N,I,P> {

};

#endif //METAHEURISTICS_SELECTOR_H
