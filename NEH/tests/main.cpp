#include "FileHandler.h"
#include "NEH.h"
#include <chrono>


typedef std::chrono::high_resolution_clock clock_;

int main()
{
	FileHandler file;

	while(true)
	{
		std::vector<std::vector<double>> FSSproblem = file.nextProblemInstance();		// read next problem file
		if (FSSproblem.empty())		break;		// once we read past all input files, we get an empty problem vector
		double time;
		std::chrono::time_point<clock_> start;
		NEH neh(FSSproblem);

		// Begin experiment
		start = clock_::now();
		double result = neh.run();
		time = std::chrono::duration_cast<std::chrono::nanoseconds>(clock_::now() - start).count() / 1000000.0;		// convert ns to ms

		file.writeNEHresult(neh, time);
	}
	return 0;
}