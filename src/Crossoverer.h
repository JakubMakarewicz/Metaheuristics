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


class PMXCrossoverer;

class Crossoverer {
public:
    double crossoverProbability;
    std::mt19937 mt{ std::random_device()() };
    std::uniform_real_distribution<> distChance{ 0, 1 };
    virtual void Cross(Specimen& lhs, Specimen& rhs) {}
    Crossoverer(double crossoverProbability) : crossoverProbability(crossoverProbability) {}
    static Crossoverer& GenerateCrossoverer(std::string crossovererName, double crossoverProbability);
};
class PMXCrossoverer: public Crossoverer {
public:
    PMXCrossoverer(double crossoverProbability) : Crossoverer(crossoverProbability) {}
    void Cross(Specimen& lhs, Specimen& rhs) override;
};

#endif //METAHEURISTICS_CROSSOVERER_H
