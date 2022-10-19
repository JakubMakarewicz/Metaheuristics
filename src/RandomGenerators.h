#pragma once
#include <random>
#include "DataStructure.h"

class RandomGenerators {
public:
	static const std::uniform_real_distribution<>* distChance;
	//static const std::random_device rd;
	//static std::random_device::result_type* mt;
	static std::uniform_int_distribution<>* distStart;
	static std::vector<std::uniform_int_distribution<>*> distsEndNode;
	static std::uniform_real_distribution<>* rouletteDist;
	static void Init(DataStructure& data);
};