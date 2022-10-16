//
// Created by kuba on 10/7/22.
//

#include "Mutator.h"
void Mutator::MutateKnapsack(Specimen& specimen){
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<> distChance(0, 1);
	for (auto& i : specimen.itemGenome) {
		if (i) {
			double chance = distChance(mt);
			if (chance < this->itemMutationProbability) {
				i.flip();
			}
		}
	}
}

Mutator& Mutator::GenerateMutator(std::string mutatorName, double nodeMutationProbability, double itemMutationProbability, bool mutateKnapsack)
{
	if (mutatorName == "SWAP") {
		SwapMutator mutator(nodeMutationProbability, itemMutationProbability, mutateKnapsack);
		return mutator;
	}
	else if (mutatorName == "INVERSE") {
		InverseMutator mutator(nodeMutationProbability, itemMutationProbability, mutateKnapsack);
		return mutator;
	}
}


void SwapMutator::MutateSpecimen(Specimen& specimen){
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<> distChance(0, 1);
	std::uniform_real_distribution<> distTarget(0, specimen.nodeGenome.size());
	for (int i = 0; i < specimen.nodeGenome.size(); i++) {
		double chance = distChance(mt);
		if (chance < this->nodeMutationProbability) {
			int target = distTarget(mt);
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
	double chance = distChance(mt);
	if (chance < this->nodeMutationProbability) {
		std::uniform_int_distribution<> distStart(0, specimen.nodeGenome.size() - 2);
		int start = distStart(mt);
		std::uniform_int_distribution<> distEnd(start + 1, specimen.nodeGenome.size() - 1);
		int end = distEnd(mt);

		std::reverse(specimen.nodeGenome.begin()+start, specimen.nodeGenome.end() + end + 1);
	}
}
