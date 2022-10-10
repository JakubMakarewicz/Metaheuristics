//
// Created by kuba on 10/7/22.
//

#ifndef METAHEURISTICS_MUTATOR_H
#define METAHEURISTICS_MUTATOR_H

#include "Specimen.h"

enum MutatorEnum{
    DEFAULT
};
class DefaultMutator;

class Mutator {
public:
    double mutationProbability;

    virtual void MutateSpecimen(Specimen& specimen) = 0;
//    Mutator<N,I> GenerateMutator(MutatorEnum mutatorEnum){
//        switch (mutatorEnum) {
//            case DEFAULT: {
//                DefaultMutator<N,I> mutator{};
//                return mutator;
//            }
//        }
//    }
};
class DefaultMutator : public Mutator{
    void MutateSpecimen(Specimen &specimen) override;
};


#endif //METAHEURISTICS_MUTATOR_H
