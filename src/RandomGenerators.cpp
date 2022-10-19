#include "RandomGenerators.h"

 void RandomGenerators::Init(DataStructure& data) {
	RandomGenerators::distChance = new std::uniform_real_distribution<>(0, 1);
    RandomGenerators::distStart = new std::uniform_int_distribution<>(0, data.nodeCount - 2);
	for (int i = 0; i < data.nodeCount; i++) {
        RandomGenerators::distsEndNode.push_back(new std::uniform_int_distribution<>(i, data.nodeCount-1));
	}//
}