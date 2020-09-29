#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <sstream>
#include "Problem.h"
#include "BlindSearch.h"
#include "LocalSearch.h"

/// @brief Class which manages file operations. Reads input file, provides testing info to other classes, prints test results to output files.
class FileHandler
{
public:

	std::ifstream inFile;		/**< Input filestream */
	std::ofstream BSoutFile;	/**< Blind search output filestream */
	std::ofstream LSoutFile;	/**< Local search output filestream */

	FileHandler(std::string inPath = INPUT_FILEPATH, std::string BSoutPath = BS_OUTPUT_FILEPATH, std::string LSoutPath = LS_OUTPUT_FILEPATH);
	~FileHandler();
	std::array<double, 2> nextFunctionBounds();
	void writeBSresult(BlindSearch bs);
	void writeLSresult(LocalSearch ls, double time);

	// Getters
	inline std::vector<int> getDimensions()		{ return dimensions; };
	inline std::array<bool, Problem::NUM_FUNCTIONS> getSelectedProblems()	{ return selectedProblems; };
	inline std::vector<int> getBSiterations()	{ return BSiterations; };
	inline std::vector<double> getLSscalingParameters()		{ return LSscalingParameters; };
	inline double getLSprecision() { return LSprecision; };
	inline int getTestCases() { return testCases; };

private:
	std::vector<int> dimensions;
	std::array<bool, Problem::NUM_FUNCTIONS> selectedProblems;
	std::vector<int> BSiterations;
	std::vector<double> LSscalingParameters;
	double LSprecision;
	int testCases;

	static std::string INPUT_FILEPATH;	/**< Name of input file. Default = "input.txt" */
	static std::string BS_OUTPUT_FILEPATH;	/**< Name of output file. Default = "BS_output.txt" */
	static std::string LS_OUTPUT_FILEPATH;	/**< Name of output file. Default = "LS_output.txt" */
	std::array <std::ofstream, Problem::NUM_FUNCTIONS> LSoutFiles;	/**< Array of LS output filestream objects (one file per objective function). */


	void init();
};

