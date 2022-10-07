//
// Created by kuba on 10/7/22.
//

#ifndef METAHEURISTICS_SPECIMEN_H
#define METAHEURISTICS_SPECIMEN_H


#include <array>
#include <bitset>

template<std::size_t N, std::size_t I>
class Specimen {
public:
    std::array<int8_t, N> nodeGenome;
    std::bitset<I> itemGenome;
    Specimen(){for (int i=0;i<N;i++) this->nodeGenome.at(i)=i; this->itemGenome.set();}
    Specimen(std::array<int8_t, N> nodeGenome, std::bitset<I> itemGenome){this->nodeGenome = nodeGenome; this->itemGenome=itemGenome;}
};


#endif //METAHEURISTICS_SPECIMEN_H
