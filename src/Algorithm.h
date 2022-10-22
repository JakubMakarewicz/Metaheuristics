#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "SpecimenFactory.h"
#include "Crossoverer.h"
#include "Mutator.h"
#include "Selector.h"
#include "Config.h"
#include "DataLoader.h"
#include "RandomGenerators.h"

class Algorithm {
public: 
	Crossoverer* crossoverer;
	Mutator* mutator;
	Selector* selector;
	SpecimenFactory* specimenFactory;
	DataStructure* data;
	Config* config;
    Evaluator* evaluator;

	std::unique_ptr<std::vector<Specimen*>> population;
    std::vector<Specimen> bestSpecimens;
    std::vector<Specimen> worstSpecimens;
    std::vector<double> averageScores;

    int currentGeneration;

	Algorithm(Config& config, DataStructure& data, RandomGenerators& rand);

    static Algorithm* GenerateAlgorithm(Config& config, DataStructure& data, RandomGenerators& rand);

    void Run();
protected:
	virtual void RunIteration()=0;
	virtual void Initialize();
	virtual bool CanRun();
	virtual void Log();
	virtual void SaveGenerationResult();
};

class NonGeneticAlgorithm: public Algorithm{
public:
    NonGeneticAlgorithm(Config& config, DataStructure& data, RandomGenerators& rand): Algorithm(config, data,rand){}
protected:
	void RunIteration() override;
};

class GeneticAlgorithm : public Algorithm {
public:
	GeneticAlgorithm(Config& config, DataStructure& data, RandomGenerators& rand) : Algorithm(config, data,rand) {}
protected:
	void RunIteration() override;
};