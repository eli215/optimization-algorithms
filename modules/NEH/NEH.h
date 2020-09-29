#pragma once
#include <vector>

/// @brief Implementation of the NEH heuristic, which approximates a minimal makespan for a given permutation flow shop problem.
class NEH
{
public:
	NEH();
	NEH(std::vector<std::vector<double>> processingTimes);
	double run();

	// Getters
	inline int getNumMachines() { return numMachines; };
	inline int getNumJobs() { return numJobs; };
	inline std::vector<std::vector<double>> getProcessingTimes() { return processingTimes; };
	inline double getSolution() { return solution; };

private:
	int numMachines; /**< Number of machines in this FSS problem. */
	int numJobs; /**< Number of jobs in this FSS problem. */
	double solution; /**< The solution, or minimal makespan, for this FSS problem. */
	std::vector<std::vector<double>> processingTimes; /**< Vector of processing times for each individual job & machine. Structure: p[job][machine]. */
	
	double partialMakespan(std::vector<std::vector<double>>& p, int L);
	void moveVectorElement(std::vector<std::vector<double>>& v, int initialInd, int newInd);
	void init();
};




