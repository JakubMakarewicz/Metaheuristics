//
// Created by kuba on 10/7/22.
//

#ifndef METAHEURISTICS_MUTATOR_H
#define METAHEURISTICS_MUTATOR_H

#include "Specimen.h"
#include "RandomGenerators.h"
#include "Config.h"


class SwapMutator;
class InverseMutator;

class Mutator {
public:
    Config* config;

    RandomGenerators* rand;
    Mutator() {}
    Mutator(Config* config, RandomGenerators& rand) : config(config), rand(&rand) {}
    virtual void MutateSpecimen(Specimen& specimen) { if (this->config->mutateKnapsack) this->MutateKnapsack(specimen); }
    virtual void MutateKnapsack(Specimen& specimen);
//
    static Mutator* GenerateMutator(std::string mutatorName, Config* config, RandomGenerators& rand);
};
class SwapMutator : public Mutator{
public:
    SwapMutator(Config* config, RandomGenerators& rand) : Mutator(config, rand){}
    void MutateSpecimen(Specimen &specimen) override;
};
class InverseMutator : public Mutator {
public:
    InverseMutator(Config* config, RandomGenerators& rand) : Mutator(config, rand){}
    void MutateSpecimen(Specimen& specimen) override;
};



#endif //METAHEURISTICS_MUTATOR_H
