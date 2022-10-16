#include "Algorithm.h"

void Algorithm::Run()
{
	this->Initialize();
	while (this->CanRun()) {
		this->RunIteration();
	}
	this->Log();
}

void Algorithm::Log()
{
	std::ofstream logFile;
	logFile.open("example.csv");
	logFile.close();
}
