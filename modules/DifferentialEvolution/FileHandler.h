#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <sstream>
#include "Problem.h"
#include "DifferentialEvolution.h"

/// @brief This class manages file operations. Reads input file & provides access to its contents, prints experiment results to output file(s).
class FileHandler
{
public:

	FileHandler(std::string inPath = INPUT_FILEPATH, std::string DEoutPath = DE_OUTPUT_FILEPATH);
	~FileHandler();

	void writeDEresult(DifferentialEvolution de, double time);

	// Getters
	inline std::array<bool, Problem::NUM_FUNCTIONS> getSelectedProblems()	{ return selectedProblems; };
	inline std::array<std::array<double, 2>, Problem::NUM_FUNCTIONS> getFunctionBounds()	{ return functionBounds; };
	inline int getNumExperiments()	{ return numExperiments; };
	inline int getMaxGenerations()	{ return maxGenerations; };
	inline int getPopulationSize()	{ return populationSize; };
	inline int getDimension()	{ return dimension; };
	inline double getMutationConstant()	{ return mutationConstant; };
	inline double getCrossoverConstant() { return crossoverConstant; };

private:
	std::array<bool, Problem::NUM_FUNCTIONS> selectedProblems; /**< Objective functions to be optimized, as specified by input file. */
	int numExperiments; /**< Number of experiments to perform, as specified by input file. */
	int maxGenerations; /**< Number of DE generations to perform, as specified by input file. */
	int populationSize; /**< Number of solutions per population, as specified by input file. */
	int dimension; /**< Solution vector dimension, as specified by input file. */
	double mutationConstant; /**< DE mutation constant, as specified by input file. */
	double crossoverConstant; /**< DE crossover probability constant, as specified by input file. */
	
	std::array<std::array<double, 2>, Problem::NUM_FUNCTIONS> functionBounds;	/**< Objective function solution space bounds, as specified by input file. */
	std::ifstream inFile;	/**< Input filestream object. */
	std::array <std::ofstream, Problem::NUM_FUNCTIONS> DEoutFiles;	/**< Array of DE output filestream objects (one file per objective function). */

	void init();

	static std::string INPUT_FILEPATH;	/**< Name of input file. Default = "input.txt" */
	static std::string DE_OUTPUT_FILEPATH;	/**< Name of output file. Default = "DE_output.txt" */
};

