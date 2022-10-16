#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <SpecimenFactory.cpp>
#include <Crossoverer.cpp>
#include <Mutator.cpp>
#include <Selector.cpp>
#include "Config.h"
#include <DataLoader.cpp>
class Algorithm {
public: 
	Crossoverer* crossoverer;
	Mutator* mutator;
	Selector* selector;
	SpecimenFactory* specimenFactory;
	DataStructure* data;
	Config* config;

	Algorithm(Config& config) {
		this->config = &config;
		DataLoader dataLoader;
		dataLoader.loadData(config.dataFilePath);
		this->data = &dataLoader.data;
		this->crossoverer = &Crossoverer::GenerateCrossoverer(config.crossoverer);
		this->mutator = &Mutator::GenerateMutator(config.mutator, config.nodeMutationProbability, config.itemMutationProbability, config.mutateKnapsack);
		this->selector = &Selector::GenerateSelector(config.selector);
		this->specimenFactory = &SpecimenFactory::GenerateSpecimenFactory(config.factory, *this->data);
	}
	virtual void Run();
private:
	std::vector<Specimen> bestSpecimens;
	std::vector<double> avgScores;
	std::vector<Specimen> worstSpecimens;
	virtual void RunIteration() = 0;
	virtual void Initialize() = 0;
	virtual bool CanRun() = 0;
	virtual void Log();
};