#include "/../../Problem/src/Problem.hpp"
#include "FileHandler.h"
#include "BlindSearch.h"
#include <chrono>


typedef std::chrono::high_resolution_clock clock_;

int main()
{
	FileHandler file;
	std::vector<int> dimensions = file.getDimensions();
	std::array<bool, Problem::NUM_FUNCTIONS> selectedProblems = file.getSelectedProblems();
	std::vector<int> iterations = file.getIterations();
    int testCases = file.getTestCases();

	for (int funcId = 0; funcId < Problem::NUM_FUNCTIONS; funcId++)		// for each problem function
	{
		std::array<double, 2> solBounds = file.nextFunctionBounds();		// get solution bounds for this problem
		if (!selectedProblems[funcId])	continue;		// skip this function if it is not selected

		for (int dimInd = 0; dimInd < (int)dimensions.size(); dimInd++)
		{
			int dimension = dimensions[dimInd];
			
			bool warmupCall = true;
			for (int c = 0; c < testCases; c++)		// for each test case
			{
				Problem problem(funcId, dimension, {solBounds[0], solBounds[1]});		// create the problem
				if (warmupCall)		// one warm-up call per function, for timing
				{
					warmupCall = false;
					std::vector<double> temp = problem.generateSolutionVector();
					problem.functions[problem.getFunctionId()](temp);
				}

				for (int iterInd = 0; iterInd < (int)iterations.size(); iterInd++)		// for each max iteration value specified by input
				{
					int iteration = iterations[iterInd];
					if (iteration == 0)	break;
					BlindSearch blindSearch(problem, iteration);
                    file.writeResult(blindSearch);
				}
			}
		}
	}

	return 0;
}