#include "FileHandler.hpp"
#include <iomanip>

// Initialize static variables
std::string FileHandler::INPUT_FILEPATH = "input.txt";
std::string FileHandler::DE_OUTPUT_FILEPATH = "DE_results.csv";

/// @brief No-arg/parameterized FileHandler constructor (has default parameters). Opens input & output files, calls init() for setup.
/// @param inputFilepath (optional) String containing filepath to the desired input file.
/// @param DEoutputFilepath (optional) String containing filepath to the desired Differential Evolution output file.
/// @return An initialized FileHandler object, containing the data from the input file.
FileHandler::FileHandler(std::string inputFilepath, std::string DEoutputFilepath)
{
	INPUT_FILEPATH = inputFilepath;
	DE_OUTPUT_FILEPATH = DEoutputFilepath;

	inFile.open(INPUT_FILEPATH);
	init();
}

/// @brief FileHandler destructor. Closes open files before deleting.
/// @return
FileHandler::~FileHandler()
{
	inFile.close();
	for (int i = 0; i < (int)DEoutFiles.size(); i++) { DEoutFiles[i].close(); }
}

/// @brief Perform FileHandler setup. Read the input file and store its contents in class fields.
void FileHandler::init()
{
	std::string line;
	std::istringstream ss;

	for (int i = 0; i < 26 && inFile.good(); i++)
	{
		std::getline(inFile, line, '\n');
		ss = std::istringstream(line);

		switch (i)
		{
			case 0:		//line 1 : list of objective functions to be tested
			{
				int probId;
				std::ostringstream filePath;
				while (ss.good())
				{
					ss >> probId;
					selectedProblems[probId - 1] = true;
					filePath << 'f' << probId << '_' << DE_OUTPUT_FILEPATH;
					DEoutFiles[probId - 1] = std::ofstream(filePath.str(), std::ios_base::trunc);
					DEoutFiles[probId - 1] << "FunctionID,MaxGenerations,PopulationSize,Dimension,Time(ms),MinFitness" << '\n';	// Print column headers
					filePath.str("");		// clear stringstream contents
				}
				break;
			}
			case 1:		//line 2: number of experiments
			{
				if (ss.good()) { ss >> numExperiments; }
				break;
			}
			case 2:		//line 3: number of generations
			{
				if (ss.good()) { ss >> maxGenerations; }
				break;
			}
			case 3:		//line 4: population size (solutions per population)
			{
				if (ss.good()) { ss >> populationSize; }
				break;
			}
			case 4:		//line 5: dimensions per solution
			{
				if (ss.good()) { ss >> dimension; }
				break;
			}
			case 5:		//line 6: value of F (mutation constant)
			{
				if (ss.good()) { ss >> mutationConstant; }
				break;
			}
			case 6:		//line 7: value of CR (crossover probability constant)
			{
				if (ss.good()) { ss >> crossoverConstant; }
				break;
			}
			case 7: { break; }	//line 8: newline divider (required)

			default:		//lines 9 - 26: objective function bounds (#1...#18)
			{
				if (ss.good()) { ss >> functionBounds[i - 8][0] >> functionBounds[i - 8][1]; }	// i - 8 so we start at index 0
				break;
			}	
		} // switch
	} // for 
}

/// @brief Write the results of a BlindSearch to the corresponding output file, along with other problem info.
/// @param bs The BlindSearch object from which we will extract the problem info and search results.
void FileHandler::writeDEresult(DifferentialEvolution de, double time)
{
	Problem problem = de.getProblem();
	std::ofstream& curFile = DEoutFiles[problem.getFunctionId()];		// get the filestream for this functionID

	curFile << std::setprecision(3) << std::scientific;
	curFile << problem.getFunctionId() + 1 << ',' << de.getMaxGenerations() << ',' << de.getPopulationSize() << ','
		<< problem.getDimension() << ',' << std::fixed << time << ',' << std::scientific << de.getMinFitness() << '\n';
	curFile.flush();
}
