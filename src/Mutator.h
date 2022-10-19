//
// Created by kuba on 10/7/22.
//

#ifndef METAHEURISTICS_MUTATOR_H
#define METAHEURISTICS_MUTATOR_H

#include "Specimen.h"
#include "RandomGenerators.h"


class SwapMutator;
class InverseMutator;

class Mutator {
public:
    double nodeMutationProbability;
    double itemMutationProbability;
    bool mutateKnapsack;
    RandomGenerators* rand;
    Mutator() {}
    Mutator(double nodeMutationProbability, double itemMutationProbability, bool mutateKnapsack, RandomGenerators& rand) : nodeMutationProbability(nodeMutationProbability), itemMutationProbability(itemMutationProbability), mutateKnapsack(mutateKnapsack), rand(&rand) {}
    virtual void MutateSpecimen(Specimen& specimen) { if (this->mutateKnapsack) this->MutateKnapsack(specimen); }
    virtual void MutateKnapsack(Specimen& specimen);
//
    static Mutator* GenerateMutator(std::string mutatorName, double nodeMutationProbability, double itemMutationProbability, bool mutateKnapsack, RandomGenerators& rand);
};
class SwapMutator : public Mutator{
public:
    SwapMutator(double nodeMutationProbability, double itemMutationProbability, bool mutateKnapsack, RandomGenerators& rand) : Mutator(nodeMutationProbability, itemMutationProbability, mutateKnapsack, rand) {}
    void MutateSpecimen(Specimen &specimen) override;
};
class InverseMutator : public Mutator {
public:
    InverseMutator(double nodeMutationProbability, double itemMutationProbability, bool mutateKnapsack, RandomGenerators& rand) : Mutator(nodeMutationProbability, itemMutationProbability, mutateKnapsack, rand) {}
    void MutateSpecimen(Specimen& specimen) override;
};



#endif //METAHEURISTICS_MUTATOR_H
