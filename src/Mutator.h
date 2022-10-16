//
// Created by kuba on 10/7/22.
//

#ifndef METAHEURISTICS_MUTATOR_H
#define METAHEURISTICS_MUTATOR_H

#include "Specimen.h"

enum MutatorEnum{
    DEFAULT
};
class SwapMutator;
class InverseMutator;

class Mutator {
public:
    double nodeMutationProbability;
    double itemMutationProbability;
    bool mutateKnapsack;
    Mutator() {}
    Mutator(double nodeMutationProbability, double itemMutationProbability, bool mutateKnapsack) : nodeMutationProbability(nodeMutationProbability), itemMutationProbability(itemMutationProbability), mutateKnapsack(mutateKnapsack) {}
    virtual void MutateSpecimen(Specimen& specimen) { if (this->mutateKnapsack) this->MutateKnapsack(specimen); }
    virtual void MutateKnapsack(Specimen& specimen);

    static Mutator& GenerateMutator(std::string mutatorName, double nodeMutationProbability, double itemMutationProbability, bool mutateKnapsack) {
        if (mutatorName == "SWAP") {
            SwapMutator mutator(nodeMutationProbability, itemMutationProbability, mutateKnapsack);
            return mutator;
        }
        else if (mutatorName == "INVERSE") {
            InverseMutator mutator(nodeMutationProbability, itemMutationProbability, mutateKnapsack);
            return mutator;
        }
    }
};
class SwapMutator : public Mutator{
public:
    SwapMutator(double nodeMutationProbability, double itemMutationProbability, bool mutateKnapsack) : Mutator(nodeMutationProbability, itemMutationProbability, mutateKnapsack) {}
    void MutateSpecimen(Specimen &specimen) override;
};
class InverseMutator : public Mutator {
public:
    InverseMutator(double nodeMutationProbability, double itemMutationProbability, bool mutateKnapsack) : Mutator(nodeMutationProbability, itemMutationProbability, mutateKnapsack) {}
    void MutateSpecimen(Specimen& specimen) override;
};



#endif //METAHEURISTICS_MUTATOR_H
