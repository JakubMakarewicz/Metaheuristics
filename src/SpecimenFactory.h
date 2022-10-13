//
// Created by kuba on 10/13/22.
//

#ifndef METAHEURISTICS_SPECIMENFACTORY_H
#define METAHEURISTICS_SPECIMENFACTORY_H


#include "Specimen.h"
#include "DataStructure.h"

class SpecimenFactory {
public:
    SpecimenFactory(DataStructure* data){ this->data = data;}
    DataStructure* data;
    virtual void InitializeSpecimen(Specimen& specimen)=0;

    int GetClosest(int currentNode, std::vector<bool>& availableNodes) const;

    void GenerateGreedyItems(Specimen &specimen);
};

class RandomSpecimenFactory: public SpecimenFactory{
public:
    RandomSpecimenFactory(DataStructure* data): SpecimenFactory(data){}
    void InitializeSpecimen(Specimen& specimen) override;
};

class GreedySpecimenFactory: public SpecimenFactory{
public:
    GreedySpecimenFactory(DataStructure* data): SpecimenFactory(data){}
    void InitializeSpecimen(Specimen& specimen) override;
};
#endif //METAHEURISTICS_SPECIMENFACTORY_H
