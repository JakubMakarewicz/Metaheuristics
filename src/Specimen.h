//
// Created by kuba on 10/7/22.
//

#ifndef METAHEURISTICS_SPECIMEN_H
#define METAHEURISTICS_SPECIMEN_H


#include <array>
#include <bitset>
#include <numeric>
#include <algorithm>

template<std::size_t N, std::size_t I>
class Specimen {
public:
    std::array<int8_t, N> nodeGenome;
    std::bitset<I> itemGenome;
    double fitness=-1.0;
    void Randomize();
    Specimen();
    Specimen(std::array<int8_t, N> nodeGenome, std::bitset<I> itemGenome){this->nodeGenome = nodeGenome; this->itemGenome=itemGenome;}
    Specimen(const Specimen& other){
        *this=other;}
    Specimen<N,I>& operator=(const Specimen& rhs);

    bool operator<(const Specimen &rhs) const;

    bool operator>(const Specimen &rhs) const;

    bool operator<=(const Specimen &rhs) const;

    bool operator>=(const Specimen &rhs) const;
};

template<std::size_t N, std::size_t I>
Specimen<N, I>::Specimen() {
    for (int i=0;i<N;i++)
        this->nodeGenome.at(i)=i;
    this->itemGenome.set();
}

template<std::size_t N, std::size_t I>
void Specimen<N, I>::Randomize() {
    std::iota(this->nodeGenome.begin(), this->nodeGenome.end(), 0);
    std::random_shuffle(this->nodeGenome.begin(), this->nodeGenome.end());

    // TODO: generate items
}

template<std::size_t N, std::size_t I>
Specimen<N, I> &Specimen<N, I>::operator=(const Specimen &rhs) {
    for (int i=0;i<N;i++)
        this->nodeGenome[i]=rhs.nodeGenome[i];
    for (int i=0;i<I;i++)
        this->itemGenome.set(i, rhs.itemGenome.test(i));
    this->fitness=rhs.fitness;
    return *this;
}

template<std::size_t N, std::size_t I>
bool Specimen<N, I>::operator<(const Specimen &rhs) const {
    return fitness < rhs.fitness;
}

template<std::size_t N, std::size_t I>
bool Specimen<N, I>::operator>(const Specimen &rhs) const {
    return rhs < *this;
}

template<std::size_t N, std::size_t I>
bool Specimen<N, I>::operator<=(const Specimen &rhs) const {
    return !(rhs < *this);
}

template<std::size_t N, std::size_t I>
bool Specimen<N, I>::operator>=(const Specimen &rhs) const {
    return !(*this < rhs);
}


#endif //METAHEURISTICS_SPECIMEN_H
