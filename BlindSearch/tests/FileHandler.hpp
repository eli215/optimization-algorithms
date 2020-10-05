#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <sstream>
#include "/../../Problem/src/Problem.hpp"
#include "BlindSearch.h"

/// @brief Class which manages file operations. Reads input file, provides testing info to other classes, prints test results to output files.
class FileHandler
{
public:

	std::ifstream inFile;		/**< Input filestream */
	std::ofstream outFile;	/**< Blind search output filestream */

	FileHandler();
	FileHandler(std::string inPath, std::string outPath);
	~FileHandler();
	std::array<double, 2> nextFunctionBounds();
	void writeResult(BlindSearch bs);

	// Getters
	inline std::vector<int> getDimensions()		{ return dimensions; };
	inline std::array<bool, Problem::NUM_FUNCTIONS> getSelectedProblems()	{ return selectedProblems; };
	inline std::vector<int> getIterations()	{ return iterations; };

	inline int getTestCases() { return testCases; };

private:
	std::vector<int> dimensions;
	std::array<bool, Problem::NUM_FUNCTIONS> selectedProblems;
	std::vector<int> iterations;

	int testCases;

	static std::string INPUT_FILEPATH;	/**< Name of input file. Default = "input.txt" */
	static std::string OUTPUT_FILEPATH;	/**< Name of output file. Default = "BS_output.txt" */


	void init();
};

