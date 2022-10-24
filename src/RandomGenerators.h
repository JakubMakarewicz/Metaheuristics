#pragma once
#include "DataStructure.h"

//#if !(defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__))
#include <random>
//#endif



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