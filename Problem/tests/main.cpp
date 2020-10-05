
#include "Problem.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>

// define types for convenience
typedef std::chrono::high_resolution_clock clock_;
typedef std::chrono::time_point<clock_> time_point;
typedef std::chrono::nanoseconds ns_;
typedef std::uniform_int_distribution<>::param_type param_type;


/// @brief Driver for the Problem class.
/// @return 0
int main()
{
	// Open filestream to write results into
	//std::ofstream resultsFile;
	//resultsFile.precision(3);		// round results to 3 decimal places
	//resultsFile.open("results.txt");
	//resultsFile << "CS471 - Project 1 - Benchmark Results\n";
	//resultsFile << "--------------------------------------------------";

	for (int funInd = 0; funInd < Driver::NUM_FUNCTIONS; funInd++)
	{
		Driver::func* function = Driver::functions[funInd];		// ptr to current function
		bool firstCall = true;		// flag for executing a warm-up call
		resultsFile << "Function #" << (funInd + 1) << "\n";

		// Generate extra file for each function to 
		char fileName[18] = "";
		sprintf_s(fileName, "f%d_solution.txt", funInd + 1);

		// Preparation for random vector generation
		double lowerBound = Driver::bounds[funInd][0];
		double upperBound = Driver::bounds[funInd][1];
		double range = upperBound - lowerBound;				// Overall range
		double fpOffset = 0 + (range - (int)range);			// Floating-point component of the range

		// Set filter range for MT's random output
		Driver::intDist.param(param_type(0, (int)range - 1));		// Note: - 1 is to account for the randomized floating-point component

		for (int dimInd = 0; dimInd < Driver::NUM_DIMENSIONS; dimInd++)
		{
			int dimension = Driver::dimensions[dimInd];
			resultsFile << "\tDimension = " << dimension << "\n";

			// Accumulators for statistical analysis

																
			for (int caseNum = 0; caseNum < Driver::NUM_CASES_PER_DIMENSION; caseNum++)
			{
				resultsFile << "\t\tCase #" << std::setw(2) << std::setfill('0') << caseNum + 1 << ": ";
				std::vector<double> vector(dimension);		// Create vector of given dimension size

				// Generate random vector
				int randInt;
				double randReal;

				for (int i = 0; i < dimension; i++)
				{
					randInt = Driver::intDist(Driver::mtEngine);				// generate random int value
					randReal = Driver::realDist(Driver::mtEngine);				// generate random floating-point value
					vector[i] = lowerBound + fpOffset + randInt + randReal;		// combine, add fpOffset, store it in vector
				}

				if (firstCall)		function(vector);		// one warm-up call per function
			
				time_point start = clock_::now();
				double result = function(vector);		// execute function
				double time = std::chrono::duration_cast<ns_>(clock_::now() - start).count() / 1000000.0;		// convert ns to ms

				resultsFile << std::setprecision(3) << std::fixed << result << " " << std::setprecision(6) << time << "ms\n";		// log result & time
			}

		}
	}

	resultsFile.close();

	return 0;
}



