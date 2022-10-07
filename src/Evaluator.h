//
// Created by kuba on 10/7/22.
//

#ifndef METAHEURISTICS_EVALUATOR_H
#define METAHEURISTICS_EVALUATOR_H

#include <cstddef>
#include "DataStructure.h"
#include "Specimen.h"

template<std::size_t N, std::size_t I>
class Evaluator {
public:
    DataStructure data;
    double EvaluateSpecimen(const Specimen<N,I>& specimen);
private:
    std::tuple<double, double> GetItemsWeightAndProfitForNode(const Specimen<N,I>& specimen, int node);
};



#endif //METAHEURISTICS_EVALUATOR_H
