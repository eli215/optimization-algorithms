#pragma once

#include "../../Problem/src/Problem.hpp"

/// @brief This class contains an implementation of the Differential Evolution algorithm.
class DifferentialEvolution
{
private:

	Problem problem; /**< Defines objective function & its characteristics. */
	int maxGenerations; /**< Max number of DE generations to perform. */
	int populationSize; /**< Number of solution vectors per population. */
	double mutationConstant; /**< The mutation constant (F or lambda value) used in the DE algorithm.*/
	double crossoverConstant; /**< The crossover probability constant (CR value) used in the DE algorithm */
	std::vector<std::vector<double>> initialPopulation;	/**< The initial population P(0) for the DE algorithm. */
	std::vector<double> bestSolution; /**< The best solution encountered during the DE process; the result of the algorithm. */
	double minFitness; /**< The fitness value of the bestSolution. */

public:

	DifferentialEvolution();
	DifferentialEvolution(Problem problem, int maxGens, int popSize, double mutationConst, double crossoverConst);
	std::vector<double> run();

	// Getters
	inline Problem getProblem()		{ return problem; };
	inline int getMaxGenerations()	{ return maxGenerations; };
	inline int getPopulationSize()	{ return populationSize; };
	inline double getMutationConstant()		{ return mutationConstant; };
	inline double getCrossoverConstant()	{ return crossoverConstant; };
	inline std::vector<double> getBestSolution()	{ return bestSolution; };
	inline double getMinFitness()	{ return minFitness; };
};

