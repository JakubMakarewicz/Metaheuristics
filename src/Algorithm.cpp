#include "Algorithm.h"

void Algorithm::Run(){
	this->Initialize();
	while (this->CanRun()) {
        this->currentGeneration++;
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

void Algorithm::Initialize()
{
    this->population.clear();
    this->currentGeneration = 0;
    for (int i = 0; i < this->config->populationSize; i++) {
        Specimen* s = new Specimen();
        this->specimenFactory->InitializeSpecimen(*s);
        this->evaluator->EvaluateSpecimen(*s);
        this->population.push_back(s);
    }
}

bool Algorithm::CanRun(){
    return this->currentGeneration < this->config->generationsCount;
    //return true;
}

void Algorithm::SaveGenerationResult() {
    double worstScore = std::numeric_limits<double>::infinity();
    int worstIndex=0;
    double bestScore = INT_MIN;
    int bestIndex=0;
    double sum=0;
    for (int i =0; i<this->config->populationSize; i++){
        Specimen* specimen = this->population.at(i);
        sum+=specimen->fitness;
        if (specimen->fitness > bestScore) {
            bestScore = specimen->fitness;
            bestIndex = i;
        }
        if (specimen->fitness < worstScore){
            worstScore = specimen->fitness;
            worstIndex = i;
        }
    }
    this->bestSpecimens.push_back(*this->population.at(bestIndex));
    this->worstSpecimens.push_back(*this->population.at(worstIndex));
    this->averageScores.push_back(sum/this->config->populationSize);
}

Algorithm::Algorithm(Config& config, DataStructure& data)
{
    this->config = &config;
    this->data = &data;
    this->crossoverer = Crossoverer::GenerateCrossoverer(config.crossoverer, config.crossoverProbability);
    this->mutator = Mutator::GenerateMutator(config.mutator, config.nodeMutationProbability, config.itemMutationProbability, config.mutateKnapsack);
    this->selector = Selector::GenerateSelector(config.selector, config.tournamentBatchSize);
    this->specimenFactory = SpecimenFactory::GenerateSpecimenFactory(config.factory, *this->data);
    this->evaluator = new Evaluator(*this->data);
    this->currentGeneration = 0;
}

Algorithm* Algorithm::GenerateAlgorithm(Config& config, DataStructure& data){
    if (config.algorithm == "NON_GENETIC"){
        NonGeneticAlgorithm* algorithm = new NonGeneticAlgorithm{config, data};
        return algorithm;
    }
    else if (config.algorithm == "GENETIC") {
        GeneticAlgorithm* algorithm = new GeneticAlgorithm{ config, data };
        return algorithm;
    }
}

void NonGeneticAlgorithm::RunIteration() {
    for (int i = 0; i<this->config->populationSize; i++){
        this->specimenFactory->InitializeSpecimen(*this->population.at(i));
        this->evaluator->EvaluateSpecimen(*this->population.at(i));
    }
}

void GeneticAlgorithm::RunIteration() {
    for (int i = 0; i < this->config->populationSize; i++) {
        this->selector->RunSelection(this->population);
        for (int i = 0; i < this->population.size(); i += 2)
            this->crossoverer->Cross(this->population.at(i), this->population.at(i + 1));// TODO
        this->evaluator->EvaluateSpecimen(*this->population.at(i));
    }
}