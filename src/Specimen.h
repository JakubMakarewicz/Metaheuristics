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

class Specimen {
public:
    std::vector<int32_t> nodeGenome;
    std::vector<bool> itemGenome;
    double fitness=-1.0;
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
};


#endif //METAHEURISTICS_SPECIMEN_H
