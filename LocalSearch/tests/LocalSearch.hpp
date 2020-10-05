#pragma once

#include "/../../Problem/src/Problem.hpp"

class LocalSearch
{
public:
	// Getters
	inline Problem getProblem() { return problem; };
	inline std::vector<double> getInitialSolution() { return initialSolution; };
	inline std::vector<double> getBestSolution() { return bestSolution; };
	inline double getMinFitness() { return minFitness; };
	inline int getIterations() { return iterations; };

	LocalSearch();		/**< No-arg constructor. */
	LocalSearch(Problem problem, double scalingParam, double precision);		/**< 3-arg constructor which generates a random initial solution. */
	LocalSearch(Problem problem, std::vector<double> initialSolution, double scalingParam, double precision);		/**< Paramaterized constructor. */
	std::vector<double> run();

protected:
	Problem problem;		/**< The problem with which we are performing a local search. */
	double scalingParam;	/**< The scaling parameter for determining neighbors in the local search. */
	double precision;
	int iterations;

	std::vector<double> initialSolution;		/**< */
	std::vector<double> bestSolution;
	double minFitness;

	bool checkNeighbors();
};

