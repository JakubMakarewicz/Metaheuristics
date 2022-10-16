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
    std::mt19937 mt{ std::random_device() };
    std::uniform_real_distribution<> distChance{ 0, 1 };
    virtual void Cross(Specimen& lhs, Specimen& rhs) {}
    static Crossoverer& GenerateCrossoverer(std::string crossovererName){
        if (crossovererName == "PMX") {
            PMXCrossoverer crossoverer;
            return crossoverer;
        }
        //else if (crossovererName == "TOURNAMENT") {
        //    TournamentSelector selector(tournamentSize);
        //    return selector;
        //}
    }
};
class PMXCrossoverer: public Crossoverer {
public:
    void Cross(Specimen& lhs, Specimen& rhs) override;
};

#endif //METAHEURISTICS_CROSSOVERER_H
