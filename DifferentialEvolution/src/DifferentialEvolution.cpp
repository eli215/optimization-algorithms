#include "DifferentialEvolution.hpp"
#include <array>

/// @brief No-arg DifferentialEvolution constructor.
/// @return A default-initialized DifferentialEvolution object.
DifferentialEvolution::DifferentialEvolution()
{
	this->problem = Problem();
	this->maxGenerations = 0;
	this->populationSize = 0;
	this->mutationConstant = 0;
	this->crossoverConstant = 0;
	this->minFitness = std::numeric_limits<double>::max();
}

/// @brief Parameterized DifferentialEvolution constructor. Generates a initial population of random solutions.
/// @param problem The Problem which defines the objective function on which DE algorithm will be performed.
/// @param maxGenerations The max number of generations to perform.
/// @param populationSize The number of solution vectors per population.
/// @param mutationConstant The mutation constant (F or lambda value) used in the DE algorithm.
/// @param crossoverConstant The crossover probability constant (CR value) used in the DE algorithm.
/// @return An initialized DifferentialEvolution object whose initialPopulation field has been prepared.
DifferentialEvolution::DifferentialEvolution(Problem problem, int maxGenerations, int populationSize, double mutationConstant, double crossoverConstant)
{
	this->problem = problem;
	this->maxGenerations = maxGenerations;
	this->populationSize = populationSize;
	this->mutationConstant = mutationConstant;
	this->crossoverConstant = crossoverConstant;
	initialPopulation = std::vector<std::vector<double>>(populationSize);		// create vector of size NP

	// INITIALIZATION: Generate initial population - P(0)
	for (int i = 0; i < populationSize; i++)
	{
		initialPopulation[i] = problem.generateRandomVector();	// generate & assign random solution vector
	}
}

/// @brief Runs the differential evolution algorithm using the given input.
/// @return The best solution encountered.
std::vector<double> DifferentialEvolution::run()
{
	Problem::func* objFunc = Problem::functions[problem.getFunctionId()];	// local copy of objective function
	int G_max = maxGenerations;
	int NP = populationSize;
	int D = problem.getDimension();
	double F = mutationConstant;
	double CR = crossoverConstant;
	double rand_j = problem.randReal_0to1();
	std::mt19937 mtEngine = problem.getMtEngine();
	std::uniform_int_distribution<int> pop_intDist(0, NP - 1);		// for population
	std::uniform_int_distribution<int> dim_intDist(0, D - 1);		// for dimension

	std::vector<std::vector<double>> x = initialPopulation;	// x represents the current population. Initialize to initialPopulation.
	std::vector<std::vector<double>> u(NP, std::vector<double>(D));	// u represents mutated (or G+1) population. Initialize all solutions with value 0.0.

	bestSolution = initialPopulation[0];	// initialize best solution to the very first solution vector
	minFitness =  objFunc(bestSolution);

	// DIFFERENTIAL EVOLUTION ALGORITHM
	for (int G = 0; G < G_max; G++)		// for each generation
	{
		for (int i = 0; i < NP; i++)	// for each member of population
		{
			int r1, r2, r3, r4;		// distinct indices of random population members
			int j_rand = dim_intDist(mtEngine);

			do { r1 = pop_intDist(mtEngine); } while (r1 == i);
			do { r2 = pop_intDist(mtEngine); } while (r2 == r1 || r2 == i);
			do { r3 = pop_intDist(mtEngine); } while (r3 == r2 || r3 == r1 || r2 == i);
			
			for (int j = 0; j < D; j++)		// for each dimension
			{
				// MUTATION
				// switch(strategy):
				if (rand_j < CR || j == j_rand)
				{
					double mutationValue = x[r3][j] + F * (x[r1][j] - x[r2][j]);

					// Values saturate to solution space bounds
					if (mutationValue < problem.getLowerBound())	u[i][j] = problem.getLowerBound();
					else if (mutationValue > problem.getUpperBound())	u[i][j] = problem.getUpperBound();
					else u[i][j] = mutationValue;
				}
				else
				{
					u[i][j] = x[i][j];
				}
			} // for (D)

			// SELECTION
			double xi_fitness = objFunc(x[i]);
			double ui_fitness = objFunc(u[i]);
			if (ui_fitness <= xi_fitness)
			{
				x[i] = u[i];
				if (ui_fitness <= minFitness)		// update global minimum
				{
					bestSolution = u[i];
					minFitness = ui_fitness;
				}
			}
		} // for (NP)
	} // for (G_max)

	return bestSolution;
}
