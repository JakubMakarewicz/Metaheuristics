#pragma once
#include <random>
#include "DataStructure.h"

class RandomGenerators {
public://
	std::uniform_real_distribution<>* distChance;
	std::uniform_int_distribution<>* distStart;
	std::vector<std::uniform_int_distribution<>*> distsEndNode;
	std::uniform_real_distribution<>* rouletteDist;
	void Init(DataStructure& data);
};