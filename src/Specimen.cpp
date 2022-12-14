//
// Created by kuba on 10/7/22.
//

#include "Specimen.h"

Specimen::Specimen(int n, int i) {
    for (int j=0;j<n;j++)
        this->nodeGenome.push_back(j);
    for (int j=0;j<i;j++)
        this->itemGenome.push_back(false);
}
//
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
    this->normalizedFitness=rhs.normalizedFitness;
    this->calculatedFitness = rhs.calculatedFitness;
    this->currentKnapsackWeight=rhs.currentKnapsackWeight;
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

bool Specimen::operator==(const Specimen& rhs) const
{
    if (this->nodeGenome.size() != rhs.nodeGenome.size() || this->itemGenome.size() != rhs.itemGenome.size())
        return false;
    for (int i = 0; i < this->nodeGenome.size(); i++)
        if (this->nodeGenome.at(i) != rhs.nodeGenome.at(i))
            return false;
    for (int i = 0; i < this->itemGenome.size(); i++)
        if (this->itemGenome.at(i) != rhs.itemGenome.at(i))
            return false;
    return true;
}

bool Specimen::PickupItem(Item &item, DataStructure& data) {
    if (this->itemGenome.size() == 0)
        for (int i = 0; i < data.items.size();i++)
            this->itemGenome.push_back(false);
    if (this->currentKnapsackWeight + item.weight <= data.knapsackCapacity){
        this->itemGenome.at(item.index) = true;
        this->currentKnapsackWeight+=item.weight;
        return true;
    }
    return false;
}

bool Specimen::IsNodeGenomeSame(const Specimen &rhs) {
    if (this->nodeGenome.size() != rhs.nodeGenome.size() || this->itemGenome.size() != rhs.itemGenome.size())
        return false;
    for (int i = 0; i < this->nodeGenome.size(); i++)
        if (this->nodeGenome.at(i) != rhs.nodeGenome.at(i))
            return false;
    return true;
}

void Specimen::CopyNodeGenome(const Specimen &rhs){
    this->nodeGenome.clear();
    for (int i=0;i<rhs.nodeGenome.size();i++)
        this->nodeGenome.push_back(rhs.nodeGenome.at(i));
}

