#include "RandomGenerators.h"

void RandomGenerators::Init(DataStructure& data) {
	//RandomGenerators::mt = new std::mt19937(std::randomde());
	//RandomGenerators::tournamentEngine = new std::mt19937(std::random_device()());
	RandomGenerators::distChance = new std::uniform_real_distribution<>(0, 1);
	RandomGenerators::distStart = new std::uniform_int_distribution<>(0, data.nodeCount - 2);
	for (int i = 0; i < data.nodeCount; i++) {
		 std::uniform_real_distribution<> distTarget(i, data.nodeCount-1);
	}
}