#include "LocalSearch.h"


LocalSearch::LocalSearch()
{
	this->problem = Problem();
	this->scalingParam = 0;
	this->bestSolution = std::vector<double>();
	this->minFitness = std::numeric_limits<double>::max();
	this->iterations = 0;
}

/// @brief 3-arg LocalSearch constructor which generates a random solution vector and calls the 4-arg constructor.
/// @param problem The Problem object with which we will perform a local search.
/// @param scalingParam
/// @param precision
/// @return An initialized LocalSearch object.
LocalSearch::LocalSearch(Problem problem, double scalingParam, double precision) 
	: LocalSearch(problem, problem.generateRandomVector(), scalingParam, precision)
{

}

/// @brief Parameterized LocalSearch constructor which executes a local search after initialization.
/// @param problem The Problem object with which we will perform a local search.
/// @param initialSolution
/// @param scalingParam
/// @param precision
/// @return A LocalSearch object containing the results of the local search.
LocalSearch::LocalSearch(Problem problem, std::vector<double> initialSolution, double scalingParam, double precision)
{
	this->problem = problem;
	this->initialSolution = initialSolution;
	this->scalingParam = scalingParam;
	this->precision = precision;
	this->minFitness = std::numeric_limits<double>::max();
	this->iterations = 0;
}

std::vector<double> LocalSearch::run()
{
	bool improved = true;

	bestSolution = initialSolution;
	minFitness = Problem::functions[problem.getFunctionId()](initialSolution);

	while(improved)
	{
		improved = checkNeighbors();
		iterations++;
	}

	return bestSolution;
	//return std::vector<double>();
}


bool LocalSearch::checkNeighbors()
{
	bool improved = false;
	std::vector<double> oldBestSolution = bestSolution;
	std::vector<double> Z(problem.getDimension());
	std::vector<double> curSolution;
	double curFitness;
	double Zi;

	for (int i = 0; i < problem.getDimension(); i++)
	{
		curSolution = oldBestSolution;		// reset localBest back to current global bestSolution
		curSolution[i] += scalingParam;		// adjust an element (and create a neighbor solution)
		if (curSolution[i] < problem.getLowerBound())	curSolution[i] = problem.getLowerBound();	// Saturate to solution space bounds
		else if (curSolution[i] > problem.getUpperBound())	curSolution[i] = problem.getUpperBound();

		curFitness = Problem::functions[problem.getFunctionId()](curSolution);
		Zi = oldBestSolution[i] - (scalingParam * (curFitness - minFitness));		// calculate gradient
		Z[i] = Zi;						// store modified element in Z set

		if (curFitness < (minFitness - precision))		// check if this neighbor solution is an improvement
		{
			minFitness = curFitness;
			bestSolution = curSolution;
			improved = true;
		}
	}

	double Zfitness = Problem::functions[problem.getFunctionId()](Z);

	if (Zfitness < (minFitness - precision))		// check if Z set is an improved solution
	{
		minFitness = Zfitness;
		bestSolution = Z;
		improved = true;
	}

	return improved;
}