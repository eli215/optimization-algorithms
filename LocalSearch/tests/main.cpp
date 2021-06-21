#include "Problem.h"
#include "FileHandler.hpp"
#include "BlindSearch.h"
#include <chrono>


typedef std::chrono::high_resolution_clock clock_;

int main()
{
	FileHandler file;
	std::vector<int> dimensions = file.getDimensions();
	std::array<bool, Problem::NUM_FUNCTIONS> selectedProblems = file.getSelectedProblems();
	std::vector<int> BSiterations = file.getBSiterations();
	std::vector<double> LSscaleParams = file.getLSscalingParameters();
	double LSprecision = file.getLSprecision();
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
				Problem problem(funcId, solBounds[0], solBounds[1], dimension);		// create the problem
				if (warmupCall)		// one warm-up call per function, for timing
				{
					warmupCall = false;
					std::vector<double> temp = problem.generateRandomVector();
					problem.functions[problem.getFunctionId()](temp);
				}

				for (int BSiterInd = 0; BSiterInd < (int)BSiterations.size(); BSiterInd++)		// for each max iteration value specified by input
				{
					int BSiteration = BSiterations[BSiterInd];
					if (BSiteration == 0)	break;
					BlindSearch blindSearch(problem, BSiteration);
					file.writeBSresult(blindSearch);
				}

				for (int LSscaleParamInd = 0; LSscaleParamInd < (int)LSscaleParams.size(); LSscaleParamInd++)		// for each scale param value specified by input
				{
					double time;
					double LSscaleParam = LSscaleParams[LSscaleParamInd];
					LocalSearch localSearch(problem, LSscaleParam, LSprecision);

					std::chrono::time_point<clock_> start = clock_::now();
					localSearch.run();
					time = std::chrono::duration_cast<std::chrono::nanoseconds>(clock_::now() - start).count() / 1000000.0;		// convert ns to ms

					file.writeLSresult(localSearch, time);
				}
			}
		}
	}

	return 0;
}