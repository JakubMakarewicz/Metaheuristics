//
// Created by kuba on 10/7/22.
//

#include "Specimen.h"
Specimen::Specimen(int n, int i) {
    for (int j=0;j<n;j++)
        this->nodeGenome.push_back(j);
    for (int j=0;j<i;j++)
        this->itemGenome.push_back(true);
}

void Specimen::Randomize() {
    std::iota(this->nodeGenome.begin(), this->nodeGenome.end(), 0);
    std::shuffle(this->nodeGenome.begin(), this->nodeGenome.end(), std::mt19937(std::random_device()()));

    // TODO: generate items
}

Specimen &Specimen::operator=(const Specimen &rhs) {
    this->nodeGenome.clear();
    this->itemGenome.clear();
    for (int i=0;i<rhs.nodeGenome.size();i++)
        this->nodeGenome.push_back(rhs.nodeGenome.at(i));
    for (int i=0;i<rhs.itemGenome.size();i++)
        this->itemGenome.push_back(rhs.itemGenome.at(i));
    this->fitness=rhs.fitness;
    return *this;
}

bool Specimen::operator<(const Specimen &rhs) const {
    return fitness < rhs.fitness;
}

bool Specimen::operator>(const Specimen &rhs) const {
    return rhs < *this;
}

bool Specimen::operator<=(const Specimen &rhs) const {
    return !(rhs < *this);
}

bool Specimen::operator>=(const Specimen &rhs) const {
    return !(*this < rhs);
}
