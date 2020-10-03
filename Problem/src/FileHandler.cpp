#include "FileHandler.hpp"
#include <iomanip>

// Initialize static variables
std::string FileHandler::PROBLEM_INSTANCE_INFILE_DIRECTORY = "DataFiles";
std::string FileHandler::OUTFILE_SUFFIX = "_NEH_results";
std::string FileHandler::OUTFILE_DIRECTORY = "Results";

/// @brief No-arg/parameterized FileHandler constructor (has default parameters). Opens input & output files, calls init() for setup.
/// @param infileDirectory (optional) String containing filepath to the desired input file directory.
/// @param NEHoutfileSuffix (optional) String containing name of desired output file suffix (excluding file extension).
/// @return An initialized FileHandler object, containing the data from the input file.
FileHandler::FileHandler(std::string infileDirectory, std::string NEHoutfileSuffix)
{
	this->PROBLEM_INSTANCE_INFILE_DIRECTORY = infileDirectory;
	this->OUTFILE_SUFFIX = NEHoutfileSuffix;
	this->lastFileOpened = "";
	this->problemInstanceInfileIterator = std::filesystem::directory_iterator(PROBLEM_INSTANCE_INFILE_DIRECTORY);

	std::filesystem::create_directory(OUTFILE_DIRECTORY);	// Create output file directory
}

/// @brief FileHandler destructor. Closes open files before deleting.
/// @return
FileHandler::~FileHandler()
{
	for (std::map<std::pair<int, int>, std::ofstream>::iterator itr = NEHoutfiles.begin(); itr != NEHoutfiles.end(); itr++)
	{
		itr->second.close();
	}
}

/// @brief Open the next input file, read its contents into a vector, and return it.
/// @return The vector<vector<double>> of [job][machine] processing times read from an input file.
std::vector<std::vector<double>> FileHandler::nextProblemInstance()
{
	std::vector<std::vector<double>> curProblemInstance;
	if (problemInstanceInfileIterator._At_end())		return curProblemInstance;		// Return empty vector if end is reached.
	
	std::ifstream curFile(problemInstanceInfileIterator->path());
	lastFileOpened = problemInstanceInfileIterator->path().filename().stem().string();		// store filename
	int numMachines, numJobs;
	std::string line;

	std::getline(curFile, line);
	std::istringstream ss = std::istringstream(line);
	ss >> numMachines >> numJobs;		// read first line of input file

	curProblemInstance = std::vector<std::vector<double>>(numJobs, std::vector<double>(numMachines));		// allocate vector - [job][machine]

	for (int m = 0; m < numMachines && curFile.good(); m++)		// for each machine  (line of file)
	{
		std::getline(curFile, line);
		ss = std::istringstream(line);

		for (int j = 0; j < numJobs && ss.good(); j++)		// for each job (space-separated value on a line)
		{
			ss >> curProblemInstance[j][m];		// store value in vector
		}
	}

	curFile.close();
	problemInstanceInfileIterator++;		// increment iterator to the next file in the directory
	return curProblemInstance;
}

/// @brief Write the results of a FSS problem solved by the NEH algorithm to the corresponding output file.
/// @param neh The NEH object from which we will extract the problem info and results.
/// @param time The algorithm processing time it took to produce this result.
void FileHandler::writeNEHresult(NEH neh, double time)
{
	std::pair key = std::make_pair(neh.getNumMachines(), neh.getNumJobs());

	if (NEHoutfiles.find(key) == NEHoutfiles.end())		// create output file if not yet created for this problem size
	{
		std::string filename = std::to_string(neh.getNumMachines()) + 'M' + std::to_string(neh.getNumJobs()) + 'J' + OUTFILE_SUFFIX + ".csv";
		NEHoutfiles[key] = std::ofstream(OUTFILE_DIRECTORY + '\\' + filename);
		NEHoutfiles[key] << "InputFileName,Result,Time\n";		// print column headers
	}

	NEHoutfiles[key] << lastFileOpened << ',' << neh.getSolution() << ',' << time << '\n';
	NEHoutfiles[key].flush();
}
