#include "FileHandler.h"
#include <iomanip>

// Initialize static variables
std::string FileHandler::INPUT_FILEPATH = "input.txt";
std::string FileHandler::OUTPUT_FILEPATH = "BS_results.csv";

/// @brief No-arg/parameterized FileHandler constructor (has default parameters). Opens input & output files, calls init() for setup.
/// @param inputFilepath (optional) String containing filepath to the desired input file.
/// @param BSoutputFilepath (optional) String containing filepath to the desired Blind Search output file (which will be generated).
/// @param LSoutputFilepath (optional) String containing filepath to the desired Local Search output file (which will be generated).
/// @return An initialized FileHandler object, which is ready for future calls to nextFunctionBounds().
FileHandler::FileHandler(std::string inputFilepath, std::string outputFilepath)
{
	INPUT_FILEPATH = inputFilepath;
	OUTPUT_FILEPATH = outputFilepath;

	inFile.open(INPUT_FILEPATH);
	outFile.open(OUTPUT_FILEPATH, std::ios_base::trunc);
	outFile << std::setprecision(3) << std::scientific;

	init();
}

/// @brief FileHandler destructor. Closes open files before deleting.
/// @return
FileHandler::~FileHandler()
{
	inFile.close();
	outFile.close();
}

/// @brief Perform initial FileHandler setup. Read the first few lines from input file for testing info.
void FileHandler::init()
{
	std::string line;
	std::istringstream ss;

	for (int i = 0; i < 7 && std::getline(inFile, line, '\n'); i++)
	{
		ss = std::istringstream(line);

		switch (i)
		{
			case 0:		// First line: dimensions
				int dim;
				while (ss.good())
				{
					ss >> dim;
					dimensions.push_back(dim);
				}
				break;
			case 1:		// Second line: which functions are being tested
			{
				int probId;
				std::ostringstream filePath;
				while (ss.good())
				{
					ss >> probId;
					selectedProblems[probId - 1] = true;
					filePath << 'f' << probId << '_' << OUTPUT_FILEPATH;
					outFiles[probId - 1] = std::ofstream(filePath.str(), std::ios_base::trunc);
					outFiles[probId - 1] << "ProblemID,Dimension,,Time(ms),Fitness" << '\n';	// Print column headers
					filePath.str("");		// clear stringstream contents
				}
				break;
			}
			case 2:		// Third line: test cases
				if (ss.good())		ss >> testCases;
				break;
			case 3:		// Fourth line: max iterations for blind search
				int numIter;
				while (ss.good())
				{
					ss >> numIter;
					iterations.push_back(numIter);
				}
				break;
			case 4:		// Fifth line: scaling parameters for local search
				double scaleParam;
				while (ss.good())
				{
					ss >> scaleParam;
					//LSscalingParameters.push_back(scaleParam);
				}
				break;
			case 5:		// Sixth line: precision 
				//if (ss.good())	ss >> LSprecision;
				break;
			case 6:		// Seventh line: newline divider
				break;
		}
	}

	// Print column headings to output files
	outFile << "ProblemID,Dimension,Iterations,Fitness,Solution" << std::endl;
}

/// @brief Read in the next set of solution space bounds from the input file.
/// @return A double[2] array where [0] = lowerBound and [1] = upperBound.
std::array<double, 2> FileHandler::nextFunctionBounds()
{
	std::array<double, 2> bounds{ 0, 0 };

	if (inFile.good())	inFile >> bounds[0] >> bounds[1];

	return bounds;
}

/// @brief Write the results of a BlindSearch to the corresponding output file, along with other problem info.
/// @param bs The BlindSearch object from which we will extract the problem info and search results.
void FileHandler::writeResult(BlindSearch bs)
{
	Problem problem = bs.getProblem();
	std::vector<double> solution = bs.getBestSolution();

	outFile << problem.getFunctionId() + 1 << ',' << problem.getDimension() << ',' << bs.getIterations() << ',' << bs.getMinFitness();

	outFile << ",{" << solution[0];
	for (int i = 1; i < (int)solution.size(); i++)
	{
		outFile << ',' << solution[i];
	}
	outFile << '}' << std::endl;
}

/// @brief Write the results of a LocalSearch to the corresponding output file, along with other problem info.
/// @param ls The LocalSearch object from which we will extract the problem info and search results.
void FileHandler::writeLSresult(LocalSearch ls, double time)
{
	Problem problem = ls.getProblem();
	//std::vector<double> solution = ls.getBestSolution();
	
	std::ofstream& curFile = LSoutFiles[problem.getFunctionId()];		// get the filestream for this functionID

	curFile << std::setprecision(3) << std::scientific;
	curFile << problem.getFunctionId() + 1 << ',' << problem.getDimension() << ',' << ls.getIterations() << ',' << std::fixed << time << ',' << std::scientific << ls.getMinFitness() << '\n';

	//LSoutFile << ",{" << solution[0];
	//for (int i = 1; i < (int)solution.size(); i++)
	//{
	//	LSoutFile << ',' << solution[i];
	//}
	//LSoutFile << '}' << std::endl;
}