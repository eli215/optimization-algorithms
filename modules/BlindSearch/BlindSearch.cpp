
#include "BlindSearch.h"

/// @brief No-arg BlindSearch constructor which sets default values for all fields.
/// @return A default-initialized BlindSearch object.
BlindSearch::BlindSearch()
{
	this->problem = Problem();
	this->bestSolution = std::vector<double>();
	this->minFitness = std::numeric_limits<double>::max();
}

/// @brief 2-arg BlindSearch constructor which generates a random solution vector and calls the 3-arg constructor.
/// @param problem The Problem object with which we will perform a blind search.
/// @return An initialized BlindSearch object.
BlindSearch::BlindSearch(Problem problem, int iterations) : BlindSearch(problem, iterations, problem.generateRandomVector())
{

}

/// @brief Parameterized BlindSearch constructor which executes a blind search after initialization.
/// @param problem The Problem object with which we will perform a blind search.
/// @return A BlindSearch object containing the results of the blind search.
BlindSearch::BlindSearch(Problem problem, int iterations, std::vector<double> initialSolution)
{
	this->problem = problem;
	this->iterations = iterations;
	this->initialSolution = initialSolution;
	this->minFitness = std::numeric_limits<double>::max();
	this->run();		// run the blind search upon upon construction
}

/// @brief Execute the blind search.
/// @return The best solution encountered.
std::vector<double> BlindSearch::run()
{
	std::vector<double> solution;
	double fitness;
	bestSolution = initialSolution;
	minFitness = Problem::functions[problem.getFunctionId()](initialSolution);

	for (int i = 0; i < iterations; i++)
	{
		solution = problem.generateRandomVector();
		fitness = Problem::functions[problem.getFunctionId()](solution);
		if (fitness < minFitness)
		{
			minFitness = fitness;
			bestSolution = solution;
		}
	}
	
	return bestSolution;
}