#pragma once

#include <vector>
#include <float.h>
#include "Problem.h"

/**
 * Class which carries out a blind search on a given problem.
 */
class BlindSearch
{
public:
	// Getters
	inline Problem getProblem() { return problem; };
	inline std::vector<double> getBestSolution() { return bestSolution; };
	inline double getMinFitness() { return minFitness; };
	inline int getIterations() { return iterations; };

	//int problemId;		/**< The Problem class problem ID of the function we're searching. */
	//int iterations;		/**< Max number of search iterations to carry out. */
	//int dimension;		/**< Dimension of solution vector */
	BlindSearch();		/**< No-arg constructor. */
	BlindSearch(Problem problem, int iterations);
	BlindSearch(Problem problem, int iterations, std::vector<double> initialSolution);		/**< Paramaterized constructor. */

protected:
	Problem problem;
	std::vector<double> initialSolution;
	std::vector<double> bestSolution;
	double minFitness;
	int iterations;

	std::vector<double> run();
};
