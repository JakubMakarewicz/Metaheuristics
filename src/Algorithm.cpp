#include "Algorithm.h"
#include "RandomGenerators.h"

void Algorithm::Run(){
	this->Initialize();
    this->SaveGenerationResult();

	while (this->CanRun()) {
        this->currentGeneration++;

		this->RunIteration();

        this->SaveGenerationResult();
        std::cout << this->currentGeneration << '\n';
	}
	this->Log();
}

void Algorithm::Log(){
	std::ofstream logFile;
    logFile.open(this->config->outputFilePath);
    for (int i = 0; i < this->currentGeneration; i++) {
        logFile << std::fixed<< this->goats.at(i) << ',' << this->bestSpecimens.at(i) << ',' << this->worstSpecimens.at(i) << ',' << this->averageScores.at(i)<< ','<<i;
        logFile << '\n';
    }
	logFile.close();
}

void Algorithm::Initialize()
{
    this->population = std::make_unique<std::vector<Specimen*>>();
//    this->population.clear();
    this->currentGeneration = 0;
    for (int i = 0; i < this->config->populationSize; i++) {
        Specimen* s = new Specimen();
        this->specimenFactory->InitializeSpecimen(*s);
        this->evaluator->EvaluateSpecimen(*s);
        this->population->push_back(s);
    }
}

bool Algorithm::CanRun(){
    return this->currentGeneration < this->config->generationsCount;
}

void Algorithm::SaveGenerationResult() {
    if (this->population->size() == 0)
        return;
    double worstScore = std::numeric_limits<double>::infinity();
    int worstIndex=0;
    double bestScore = INT_MIN;
    int bestIndex=0;
    double sum=0;
    for (int i =0; i<this->population->size(); i++){
        Specimen* specimen = this->population->at(i);
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
    if (this->goats.size() == 0)
        this->goats.push_back(this->population->at(bestIndex)->fitness);
    else if (this->population->at(bestIndex)->fitness > this->goats.back())
        this->goats.push_back(this->population->at(bestIndex)->fitness);
    else this->goats.push_back(this->goats.back());
    this->bestSpecimens.push_back(this->population->at(bestIndex)->fitness);
    this->worstSpecimens.push_back(this->population->at(worstIndex)->fitness);
    this->averageScores.push_back(sum/this->config->populationSize);
}

Algorithm::Algorithm(Config& config, DataStructure& data, RandomGenerators& rand)
{
    this->config = &config;
    this->data = &data;
    this->rand = &rand;
    this->crossoverer = Crossoverer::GenerateCrossoverer(config.crossoverer, config.crossoverProbability, rand);
    this->mutator = Mutator::GenerateMutator(config.mutator, this->config, rand);
    this->selector = Selector::GenerateSelector(config.selector, config.tournamentBatchSize, rand);
    this->specimenFactory = SpecimenFactory::GenerateSpecimenFactory(config.factory, *this->data, rand);
    this->evaluator = new Evaluator(*this->data);
    this->currentGeneration = 0;
}

Algorithm* Algorithm::GenerateAlgorithm(Config& config, DataStructure& data, RandomGenerators& rand){
    if (config.algorithm == "NON_GENETIC"){
        NonGeneticAlgorithm* algorithm = new NonGeneticAlgorithm{config, data,rand};
        return algorithm;
    }
    else if (config.algorithm == "GENETIC") {
        GeneticAlgorithm* algorithm = new GeneticAlgorithm{ config, data,rand};
        return algorithm;
    }
    else if (config.algorithm == "TABOO") {
        TabooSearch* algorithm = new TabooSearch{ config, data,rand };
        return algorithm;
    }
    else if (config.algorithm == "SA") {
        SimulatedAnnealing* algorithm = new SimulatedAnnealing{ config, data,rand };
        return algorithm;
    }
}

void NonGeneticAlgorithm::RunIteration() {
    for (int i = 0; i<this->config->populationSize; i++){
        this->specimenFactory->InitializeSpecimen(*this->population->at(i));
        this->evaluator->EvaluateSpecimen(*this->population->at(i));
    }
}

void GeneticAlgorithm::RunIteration() {
//    for (int i = 0; i < this->config->populationSize; i++) {
    this->population = this->selector->RunSelection(*this->population);
    for (int i = 0; i < this->population->size(); i += 2) {
        this->crossoverer->Cross(*this->population->at(i), *this->population->at(i));
    }
    for (int i = 0; i < this->population->size(); i++) {
        this->mutator->MutateSpecimen(*this->population->at(i));
        if (this->config->generateGreedyKnapsackPostCross)
            this->specimenFactory->GenerateGreedyItems(*this->population->at(i));
        if (this->config->mutateKnapsack)
            this->mutator->MutateKnapsack(*this->population->at(i));
        this->evaluator->EvaluateSpecimen(*this->population->at(i));
    }

//    }
}


void TabooSearch::FindNeighbourhood()
{
    for (int i = 0; i < this->config->populationSize; i++) {
        Specimen* spec = new Specimen();
        spec->CopyNodeGenome(*this->currentSpecimen);
//        Specimen* spec = new Specimen(*this->currentSpecimen);
        this->mutator->MutateSpecimen(*spec);
        bool inTaboo=false;
        for (auto const& i: this->taboo) {
            if (spec->IsNodeGenomeSame(*i)) {
                inTaboo = true;
                break;
            }
        }
        if (inTaboo) {
            delete spec;
            continue;
        }
        if (this->config->generateGreedyKnapsackPostCross)
            this->specimenFactory->GenerateGreedyItems(*spec);
        this->population->push_back(spec);
    }
}

void TabooSearch::Initialize() {
    this->currentSpecimen = new Specimen();
    this->specimenFactory->InitializeSpecimen(*this->currentSpecimen);
    this->currentGeneration = 0;
    this->population = std::make_unique<std::vector<Specimen*>>();
    this->evaluator->EvaluateSpecimen(*this->currentSpecimen);

}
void TabooSearch::RunIteration() {
    for (int i = 0; i < this->population->size(); i++)
        delete this->population->at(i);
    this->population->clear();
    this->FindNeighbourhood();
    double maxScore = INT_MIN;
    int bestIndex = 0;
    for (int i = 0; i < this->population->size();i++) {
        this->evaluator->EvaluateSpecimen(*this->population->at(i));
        if (this->population->at(i)->fitness > maxScore) {
            maxScore = this->population->at(i)->fitness;
            bestIndex = i;
        }
    }
    delete this->currentSpecimen;
    this->currentSpecimen = new Specimen(*this->population->at(bestIndex));
    this->taboo.push_back(new Specimen(*this->population->at(bestIndex)));
    if (this->taboo.size() > this->config->tabooSize){
        delete this->taboo.front();
        this->taboo.pop_front();
    }
}

void SimulatedAnnealing::FindNeighbourhood()
{
    for (int i = 0; i < this->config->populationSize; i++) {
        Specimen* spec = new Specimen();
        spec->CopyNodeGenome(*this->currentSpecimen);
        this->mutator->MutateSpecimen(*spec);
        if (this->config->generateGreedyKnapsackPostCross)
            this->specimenFactory->GenerateGreedyItems(*spec);
        this->population->push_back(spec);
    }
}

void SimulatedAnnealing::Initialize() {
    this->currentSpecimen = new Specimen();
    this->specimenFactory->InitializeSpecimen(*this->currentSpecimen);
    this->evaluator->EvaluateSpecimen(*this->currentSpecimen);
    this->currentGeneration = 0;
    this->population = std::make_unique<std::vector<Specimen*>>();
}
void SimulatedAnnealing::RunIteration() {
    for (int i = 0; i < this->population->size(); i++)
        delete this->population->at(i);
    this->population->clear();
    this->FindNeighbourhood();
    double maxScore = INT_MIN;
    int bestIndex = 0;
    for (int i = 0; i < this->population->size();i++) {
        this->evaluator->EvaluateSpecimen(*this->population->at(i));
        if (this->population->at(i)->fitness > maxScore) {
            maxScore = this->population->at(i)->fitness;
            bestIndex = i;
        }
    }
    if (maxScore > this->currentSpecimen->fitness) {
        delete this->currentSpecimen;
        this->currentSpecimen = new Specimen(*this->population->at(bestIndex));
    }
    else if (((*rand->distChance)(*rand->mt)) < std::exp((maxScore - this->currentSpecimen->fitness) / temperature)) {
        delete this->currentSpecimen;
        this->currentSpecimen = new Specimen(*this->population->at(bestIndex));
    }
    this->temperature = this->temperature * this->config->annealingRatio;
}

void SimulatedAnnealing::SaveGenerationResult()
{
    if (this->goats.size() == 0)
        this->goats.push_back(this->currentSpecimen->fitness);
    else if (this->currentSpecimen->fitness > this->goats.back())
        this->goats.push_back(this->currentSpecimen->fitness);
    else this->goats.push_back(this->goats.back());
    this->bestSpecimens.push_back(this->currentSpecimen->fitness);
    this->worstSpecimens.push_back(this->currentSpecimen->fitness);
    this->averageScores.push_back(this->currentSpecimen->fitness);
}


bool SimulatedAnnealing::CanRun() {
    bool test =  Algorithm::CanRun() && this->temperature > this->config->targetTemperature;
    return test;
}