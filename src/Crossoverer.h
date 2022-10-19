//
// Created by kuba on 10/7/22.
//

#ifndef METAHEURISTICS_CROSSOVERER_H
#define METAHEURISTICS_CROSSOVERER_H

#include <cstddef>
#include "Specimen.h"
#include "RandomGenerators.h"
#include <unordered_map>

enum CrossoverEnum{
    DEFAULT
};


class PMXCrossoverer;

class Crossoverer {
public:
    double crossoverProbability;
    RandomGenerators* rand;

    virtual void Cross(Specimen& lhs, Specimen& rhs) {}
    Crossoverer(double crossoverProbability, RandomGenerators& rand) : crossoverProbability(crossoverProbability), rand(&rand) {}
    static Crossoverer* GenerateCrossoverer(std::string crossovererName, double crossoverProbability, RandomGenerators& rand);//
};
class PMXCrossoverer: public Crossoverer {
public:
    PMXCrossoverer(double crossoverProbability, RandomGenerators& rand) : Crossoverer(crossoverProbability,rand) {}
    void Cross(Specimen& lhs, Specimen& rhs) override;
private:
    std::unordered_map<int, int> mappingLhsRhs;
    std::unordered_map<int, int> mappingRhsLhs;
};

#endif //METAHEURISTICS_CROSSOVERER_H
