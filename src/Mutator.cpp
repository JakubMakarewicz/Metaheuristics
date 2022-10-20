//
// Created by kuba on 10/7/22.
//

#include "Mutator.h"
#include "RandomGenerators.h"
//
void Mutator::MutateKnapsack(Specimen& specimen){
	//std::random_device rd;
	//std::mt19937_64 mt(rd());
	for (int i = 0; i < specimen.itemGenome.size();i++) {
        if (specimen.itemGenome.at(i)) {
            double chance = (*rand->distChance)(*rand->mt);
            if (chance < this->itemMutationProbability) {
				specimen.itemGenome.at(i).flip();
            }
        }
    }
}

Mutator* Mutator::GenerateMutator(std::string mutatorName, double nodeMutationProbability, double itemMutationProbability, bool mutateKnapsack, RandomGenerators& rand)
{
	if (mutatorName == "SWAP") {
		return new SwapMutator(nodeMutationProbability, itemMutationProbability, mutateKnapsack, rand);
	}
	else if (mutatorName == "INVERSE") {
		return new InverseMutator(nodeMutationProbability, itemMutationProbability, mutateKnapsack,rand);
	}
}


void SwapMutator::MutateSpecimen(Specimen& specimen){
	//std::random_device rd;
	//std::mt19937_64 mt(rd());
//    if (this->mutateKnapsack) this->MutateKnapsack(specimen);
	for (int i = 0; i < specimen.nodeGenome.size(); i++) {
		double chance = (*rand->distChance)(*rand->mt);
		if (chance < this->nodeMutationProbability) {
			int target = (*rand->distsEndNode.at(0))(*rand->mt);
			int temp = specimen.nodeGenome.at(i);
			specimen.nodeGenome.at(i) = specimen.nodeGenome.at(target);
			specimen.nodeGenome.at(target) = temp;
		}
	}
}

void InverseMutator::MutateSpecimen(Specimen& specimen)
{
    //std::random_device rd;
    //std::mt19937_64 mt(rd());
//    if (this->mutateKnapsack) this->MutateKnapsack(specimen);
	double chance = (*rand->distChance)(*rand->mt);
	if (chance < this->nodeMutationProbability) {
		int start = (*rand->distStart)(*rand->mt);
		int end = (*rand->distsEndNode.at(start+1))(*rand->mt);

		std::reverse(specimen.nodeGenome.begin()+start, specimen.nodeGenome.begin() + end + 1);
	}
}
