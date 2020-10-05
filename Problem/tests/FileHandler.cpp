#include "FileHandler.hpp"
#include <iomanip>

// Initialize static variables
std::string FileHandler::INPUT_FILEPATH = "input.txt";
std::string FileHandler::OUTPUT_FILEPATH = "results.csv";


/// @brief No-arg/parameterized FileHandler constructor (has default parameters). Opens input & output files, calls init() for setup.
/// @param inFilePath String containing filepath to the desired input file directory.
/// @return An initialized FileHandler object, containing the data from the input file.
FileHandler::FileHandler(std::string inFilePath)
{
    inFile.open(inFilePath);

    init();
}

/// @brief FileHandler destructor. Closes open files before deleting.
/// @return
FileHandler::~FileHandler()
{

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
            case 0:		// First line: dimension(s)
            {
                int dim;
                while (ss.good()) {
                    ss >> dim;
                    dimensions.push_back(dim);
                }
                break;
            }
            case 1:		// Second line: which functions are being tested
            {
                int probId;
                std::ostringstream fileName;
                while (ss.good())
                {
                    ss >> probId;
                    selectedProblems[probId - 1] = true;
                    fileName << 'f' << probId << '_' << "output";
                    outFiles[probId - 1] = std::ofstream(fileName.str(), std::ios_base::trunc);
                    outFiles[probId - 1] << "ProblemID,Dimension,Iterations,Time(ms),Fitness" << '\n';	// Print column headers
                    fileName.str("");		// clear stringstream contents
                }
                break;
            }
            case 2:		// Third line: test cases
                if (ss.good())		ss >> iterations;
                break;
            case 6:		// Seventh line: newline divider
                break;
        }
    }

    // Print column headings to output files
    outFile << "ProblemID,Dimension,Iterations,Fitness,Solution" << std::endl;
}


/// @brief Write the results of a Problem to an output file corresponding to its function id.
/// @param Problem The Problem object which contains the parameters of this iteration.
/// @param time The processing time elapsed to produce this result.
void FileHandler::writeResult(Problem *problem, double result, double time)
{

}
