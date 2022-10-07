//
// Created by kuba on 10/7/22.
//

#ifndef METAHEURISTICS_MUTATOR_H
#define METAHEURISTICS_MUTATOR_H

#include "Specimen.h"

enum MutatorEnum{
    DEFAULT
};
template<std::size_t N, std::size_t I>
class DefaultMutator;

template<std::size_t N, std::size_t I>
class Mutator {
public:
    double mutationProbability;

    virtual void MutateSpecimen(Specimen<N,I>& specimen) = 0;
    Mutator<N,I> GenerateMutator(MutatorEnum mutatorEnum){
        switch (mutatorEnum) {
            case DEFAULT: {
                DefaultMutator<N,I> mutator{};
                return mutator;
            }
        }
    }
};
template<std::size_t N, std::size_t I>
class DefaultMutator : public Mutator<N,I>{
    void MutateSpecimen(Specimen<N, I> &specimen) override;
};


#endif //METAHEURISTICS_MUTATOR_H
