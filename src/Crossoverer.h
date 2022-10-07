//
// Created by kuba on 10/7/22.
//

#ifndef METAHEURISTICS_CROSSOVERER_H
#define METAHEURISTICS_CROSSOVERER_H

#include <cstddef>
#include "Specimen.h"

enum CrossoverEnum{
    DEFAULT
};


template<std::size_t N, std::size_t I>
class DefaultCrossoverer;

template<std::size_t N, std::size_t I>
class Crossoverer {
    double crossoverProbability;

    virtual void Cross(Specimen<N,I> lhs, Specimen<N,I> rhs)=0;
//    Crossoverer<N,I> GenerateCrossoverer(CrossoverEnum crossoverEnum){
//        switch (crossoverEnum) {
//            case DEFAULT: {
//                DefaultCrossoverer<N,I> mutator{};
//                return mutator;
//            }
//        }
//    }
};
template<std::size_t N, std::size_t I>
class DefaultCrossoverer: public Crossoverer<N,I> {
    void Cross(Specimen<N, I> lhs, Specimen<N, I> rhs) override;
};

#endif //METAHEURISTICS_CROSSOVERER_H
