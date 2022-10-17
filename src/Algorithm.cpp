#include "Algorithm.h"

void Algorithm::Run(){
	this->Initialize();
	while (this->CanRun()) {
		this->RunIteration();
        this->SaveGenerationResult();
	}
	this->Log();
}

void Algorithm::Log(){
	std::ofstream logFile;
	logFile.open("example.csv");
	logFile.close();
}
void Algorithm::Initialize(){
    this->population.clear();
    this->currentGeneration=0;
    for (int i =0; i<this->config->populationSize; i++){
        Specimen s;
        this->specimenFactory->InitializeSpecimen(s);
        this->evaluator->EvaluateSpecimen(s);
        this->population.push_back(s);
    }
}
bool Algorithm::CanRun(){
    return this->currentGeneration<this->config->generationsCount;
}

void Algorithm::RunIteration(){
    throw;}

void Algorithm::SaveGenerationResult() {
    double worstScore = std::numeric_limits<double>::infinity();
    int worstIndex=0;
    double bestScore = INT_MIN;
    int bestIndex=0;
    double sum=0;
    for (int i =0; i<this->config->populationSize; i++){
        Specimen & specimen = this->population.at(i).get();
        sum+=specimen.fitness;
        if (specimen.fitness > bestScore) {
            bestScore = specimen.fitness;
            bestIndex = i;
        }
        if (specimen.fitness < worstScore){
            worstScore = specimen.fitness;
            worstIndex = i;
        }
    }
    this->bestSpecimens.push_back(this->population.at(bestIndex));
    this->worstSpecimens.push_back(this->population.at(worstIndex));
    this->averageScores.push_back(sum/this->config->populationSize);
}

Algorithm& GenerateAlgorithm(Config& config, DataStructure& data){
    if (config.algorithm == "NON_GENETIC"){
        NonGeneticAlgorithm algorithm{config, data};
        return algorithm;
    }
}

void NonGeneticAlgorithm::RunIteration() {
    for (int i = 0; i<this->config->populationSize; i++){
        this->specimenFactory->InitializeSpecimen(this->population.at(i));
        this->evaluator->EvaluateSpecimen(this->population.at(i));
    }
}