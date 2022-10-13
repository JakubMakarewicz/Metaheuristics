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


class DefaultCrossoverer;

class Crossoverer {
public:
    double crossoverProbability;

    virtual void Cross(Specimen& lhs, Specimen& rhs)=0;
//    Crossoverer<N,I> GenerateCrossoverer(CrossoverEnum crossoverEnum){
//        switch (crossoverEnum) {
//            case DEFAULT: {
//                DefaultCrossoverer<N,I> mutator{};
//                return mutator;
//            }
//        }
//    }
};
class PMXCrossoverer: public Crossoverer {
public:
    void Cross(Specimen& lhs, Specimen& rhs) override;
};

#endif //METAHEURISTICS_CROSSOVERER_H
