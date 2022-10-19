#pragma once
#include <random>
#include "DataStructure.h"

class RandomGenerators {
public://
	std::uniform_real_distribution<>* distChance;
	std::uniform_int_distribution<>* distStart;
	std::vector<std::uniform_int_distribution<>*> distsEndNode;
	std::uniform_real_distribution<>* rouletteDist;
	std::random_device rd;
	std::mt19937_64* mt;
	void Init(DataStructure& data);
};