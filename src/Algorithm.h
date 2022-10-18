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
class Algorithm {
public: 
	Crossoverer* crossoverer;
	Mutator* mutator;
	Selector* selector;
	SpecimenFactory* specimenFactory;
	DataStructure* data;
	Config* config;
    Evaluator* evaluator;

    std::vector<std::reference_wrapper<Specimen>> population;
    std::vector<Specimen> bestSpecimens;
    std::vector<Specimen> worstSpecimens;
    std::vector<double> averageScores;

    int currentGeneration;

	Algorithm(Config& config, DataStructure& data);

    static Algorithm& GenerateAlgorithm(Config& config, DataStructure& data);

    void Run();
protected:
	void RunIteration();
	void Initialize();
	bool CanRun();
	void Log();
    void SaveGenerationResult();
};

class NonGeneticAlgorithm: virtual public Algorithm{
public:
    NonGeneticAlgorithm(Config& config, DataStructure& data): Algorithm(config, data){}
protected:
	void RunIteration();
	//void Initialize(){ this->Initialize(); }
};