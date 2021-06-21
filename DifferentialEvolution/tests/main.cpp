#include "Problem.h"
#include "FileHandler.hpp"
#include "DifferentialEvolution.h"
#include <chrono>


typedef std::chrono::high_resolution_clock clock_;

int main()
{
	FileHandler file;

	for (int funcId = 0; funcId < Problem::NUM_FUNCTIONS; funcId++)		// for each problem function
	{
		if (!file.getSelectedProblems()[funcId])	continue;		// skip this function if it is not selected

		bool warmupCall = true;
		for (int i = 0; i < file.getNumExperiments(); i++)		// for each test case
		{
			Problem problem(funcId, file.getFunctionBounds()[funcId][0], file.getFunctionBounds()[funcId][1], file.getDimension());		// create the problem object
			
			if (warmupCall)		// one warm-up call per function, for timing
			{
				warmupCall = false;
				std::vector<double> temp = problem.generateRandomVector();
				problem.functions[problem.getFunctionId()](temp);
			}

			double time;
			DifferentialEvolution diffEvoAlg(problem, file.getMaxGenerations(), file.getPopulationSize(), 
				file.getMutationConstant(), file.getCrossoverConstant());

			std::chrono::time_point<clock_> start = clock_::now();
			diffEvoAlg.run();
			time = std::chrono::duration_cast<std::chrono::nanoseconds>(clock_::now() - start).count() / 1000000.0;		// convert ns to ms
			
			file.writeDEresult(diffEvoAlg, time);
		}
	}

	return 0;
}