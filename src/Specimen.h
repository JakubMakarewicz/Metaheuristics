//
// Created by kuba on 10/7/22.
//

#ifndef METAHEURISTICS_SPECIMEN_H
#define METAHEURISTICS_SPECIMEN_H


#include <array>
#include <bitset>
#include <numeric>
#include <algorithm>
#include <random>
#include "Item.h"
#include "DataStructure.h"
//
class Specimen {
public:
    std::vector<int32_t> nodeGenome;
    std::vector<bool> itemGenome;
    double fitness=-1.0;
    double normalizedFitness;
    bool calculatedFitness; // TODO: use this
    double currentKnapsackWeight=0.0;
    void Randomize();
    Specimen(){}
    Specimen(int n, int i);
    Specimen(const Specimen& other){
        *this=other;}

    Specimen& operator=(const Specimen& rhs);

    bool operator<(const Specimen &rhs) const;

    bool operator>(const Specimen &rhs) const;

    bool operator<=(const Specimen &rhs) const;

    bool operator>=(const Specimen &rhs) const;

    void ClearKnapsack() { this->currentKnapsackWeight = 0; for (int i = 0;i < this->itemGenome.size(); i++)this->itemGenome.at(i) = false; }
    bool PickupItem(Item& item, DataStructure& data);

};


#endif //METAHEURISTICS_SPECIMEN_H
