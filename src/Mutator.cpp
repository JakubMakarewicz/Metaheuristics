//
// Created by kuba on 10/7/22.
//

#include "Mutator.h"
#include "RandomGenerators.h"
//
void Mutator::MutateKnapsack(Specimen& specimen){
	std::random_device rd;
	std::mt19937 mt(rd());
    for (auto && i : specimen.itemGenome){
        if (i) {
            double chance = (*rand->distChance)(mt);
            if (chance < this->itemMutationProbability) {
                i.flip();
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
	std::random_device rd;
	std::mt19937 mt(rd());
	for (int i = 0; i < specimen.nodeGenome.size(); i++) {
		double chance = (*rand->distChance)(mt);
		if (chance < this->nodeMutationProbability) {
			int target = (*rand->distsEndNode.at(0))(mt);
			int temp = specimen.nodeGenome.at(i);
			specimen.nodeGenome.at(i) = specimen.nodeGenome.at(target);
			specimen.nodeGenome.at(target) = temp;
		}
	}
}

void InverseMutator::MutateSpecimen(Specimen& specimen)
{
    std::random_device rd;
    std::mt19937 mt(rd());
	std::uniform_real_distribution<> distChance(0, 1);
	double chance = (*rand->distChance)(mt);
	if (chance < this->nodeMutationProbability) {
		int start = (*rand->distStart)(mt);
		int end = (*rand->distsEndNode.at(start+1))(mt);

		std::reverse(specimen.nodeGenome.begin()+start, specimen.nodeGenome.end() + end + 1);
	}
}
