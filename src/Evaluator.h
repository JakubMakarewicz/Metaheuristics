//
// Created by kuba on 10/7/22.
//

#ifndef METAHEURISTICS_EVALUATOR_H
#define METAHEURISTICS_EVALUATOR_H

#include <cstddef>
#include "DataStructure.h"
#include "Specimen.h"

class Evaluator {
public:
    DataStructure data;
    double EvaluateSpecimen( Specimen& specimen);
private:
    std::tuple<double, double> GetItemsWeightAndProfitForNode(const Specimen& specimen, int node);
};

#endif //METAHEURISTICS_EVALUATOR_H
