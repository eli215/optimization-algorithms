#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include "Problem.hpp"

/// @brief This class manages file operations. Reads input file and writes results to output file(s).
class FileHandler
{
public:

    FileHandler();
	FileHandler(std::string inFilePath);
	~FileHandler();

    std::array<double, 2> nextFunctionBounds();
	void writeResult(Problem *problem, double result, double time = 0);

    // Getters
    inline std::vector<int> getDimensions()		{ return dimensions; };
    inline std::array<bool, Problem::NUM_FUNCTIONS> getSelectedProblems()	{ return selectedProblems; };
    inline int getIterations()	{ return iterations; };
	
private:

    std::vector<int> dimensions;    /**< The solution dimension(s) being tested. */
    std::array<bool, Problem::NUM_FUNCTIONS> selectedProblems;  /**< A list of the benchmark functions being tested. */
    int iterations;    /**< The number of tests iterations to perform per dimension. */

    std::ifstream inFile;		/**< Input filestream */
    std::array <std::ofstream, Problem::NUM_FUNCTIONS> outFiles;    /**< Output filestreams */
    //std::ofstream outFile;	    /**< Output filestream */

    void init();
	//static std::string PROBLEM_INSTANCE_INFILE_DIRECTORY; /**< Name of the directory containing the FSS problem instance input file(s). Default = "DataFiles" */
	//static std::string OUTFILE_SUFFIX;	/**< Suffix of output file(s). Default = "_NEH_results" */
	//static std::string OUTFILE_DIRECTORY; /**< Name of the output file directory. Default = "Results" */
};

