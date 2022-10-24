//
// Created by kuba on 10/7/22.
//

#include "Mutator.h"
#include "RandomGenerators.h"
#include <iostream>
//
void Mutator::MutateKnapsack(Specimen& specimen){
	//std::random_device rd;
	//std::mt19937_64 mt(rd());
	for (int i = 0; i < specimen.itemGenome.size();i++) {
        if (specimen.itemGenome.at(i)) {
            double chance = (*rand->distChance)(*rand->mt);
            if (chance < this->config->itemMutationProbability) {
				specimen.itemGenome.at(i).flip();
            }
        }
    }
}

Mutator* Mutator::GenerateMutator(std::string mutatorName, Config* config, RandomGenerators& rand)
{
	if (mutatorName == "SWAP") {
		return new SwapMutator(config, rand);
	}
	else if (mutatorName == "INVERSE") {
		return new InverseMutator(config,rand);
	}
}


void SwapMutator::MutateSpecimen(Specimen& specimen){
	//std::random_device rd;
	//std::mt19937_64 mt(rd());
//    if (this->mutateKnapsack) this->MutateKnapsack(specimen);

	if (this->config->mutateOnlyOnce) {
		int start = (*rand->distsEndNode.at(0))(*rand->mt);
		int target = (*rand->distsEndNode.at(0))(*rand->mt);
		int temp = specimen.nodeGenome.at(start);
		specimen.nodeGenome.at(start) = specimen.nodeGenome.at(target);
		specimen.nodeGenome.at(target) = temp;
	}
	else {
		double chance = (*rand->distChance)(*rand->mt);
		if (chance > this->config->specimenNodeGenomeMutationProbability) return;
		for (int i = 0; i < specimen.nodeGenome.size(); i++) {
			chance = (*rand->distChance)(*rand->mt);
			if (chance < this->config->nodeMutationProbability) {
				int target = (*rand->distsEndNode.at(0))(*rand->mt);
				int temp = specimen.nodeGenome.at(i);
				specimen.nodeGenome.at(i) = specimen.nodeGenome.at(target);
				specimen.nodeGenome.at(target) = temp;
			}
		}
	}
}

void InverseMutator::MutateSpecimen(Specimen& specimen)
{
    //std::random_device rd;
    //std::mt19937_64 mt(rd());
	double chance = (*rand->distChance)(*rand->mt);
    if (chance > this->config->specimenNodeGenomeMutationProbability) return;
    chance = (*rand->distChance)(*rand->mt);
	if (this->config->mutateOnlyOnce) 
		chance = 0;
	if (chance < this->config->nodeMutationProbability) {
		int start = (*rand->distStart)(*rand->mt);
		int end = (*rand->distsEndNode.at(start+1))(*rand->mt);
		std::reverse(specimen.nodeGenome.begin()+start, specimen.nodeGenome.begin() + end + 1);
	}
}
