//
// Created by kuba on 10/13/22.
//

#ifndef METAHEURISTICS_SPECIMENFACTORY_H
#define METAHEURISTICS_SPECIMENFACTORY_H


#include "Specimen.h"
#include "DataStructure.h"
class RandomSpecimenFactory;
class GreedySpecimenFactory;
class SpecimenFactory {
public:
    SpecimenFactory();
    SpecimenFactory(DataStructure& data) { this->data = data; }
    DataStructure data;
    virtual void InitializeSpecimen(Specimen& specimen){}

    int GetClosest(int currentNode, std::vector<bool>& availableNodes) const;

    void GenerateGreedyItems(Specimen &specimen);

    static SpecimenFactory* GenerateSpecimenFactory(std::string specimenFactoryName, DataStructure& data);

};

class RandomSpecimenFactory: public SpecimenFactory{
public:
    RandomSpecimenFactory(DataStructure& data): SpecimenFactory(data){}
    void InitializeSpecimen(Specimen& specimen) override;
};

class GreedySpecimenFactory: public SpecimenFactory{
public:
    GreedySpecimenFactory(DataStructure& data): SpecimenFactory(data){}
    void InitializeSpecimen(Specimen& specimen) override;
};
#endif //METAHEURISTICS_SPECIMENFACTORY_H
