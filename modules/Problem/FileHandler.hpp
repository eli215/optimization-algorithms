#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include "NEH.h"
#include <filesystem>

/// @brief This class manages file operations. Reads input file & provides access to its contents, prints experiment results to output file(s).
class FileHandler
{
public:

	FileHandler(std::string infileDirectory = PROBLEM_INSTANCE_INFILE_DIRECTORY, std::string DEoutPath = OUTFILE_SUFFIX);
	~FileHandler();

	std::vector<std::vector<double>> nextProblemInstance();
	void writeNEHresult(NEH neh, double time);
	
private:
	std::filesystem::directory_iterator problemInstanceInfileIterator; /**< (C++17) Used to iterate through the directory of problem instance input files. */
	std::map<std::pair<int, int>, std::ofstream> NEHoutfiles; /**< Ordered hashmap of FSS problem instance size variants. Key = pair(#machines, #jobs). Value = output filestream. */
	std::string lastFileOpened;		/**< Name of the last file opened by nextProblemInstance(). */

	static std::string PROBLEM_INSTANCE_INFILE_DIRECTORY; /**< Name of the directory containing the FSS problem instance input file(s). Default = "DataFiles" */
	static std::string OUTFILE_SUFFIX;	/**< Suffix of output file(s). Default = "_NEH_results" */
	static std::string OUTFILE_DIRECTORY; /**< Name of the output file directory. Default = "Results" */
};

