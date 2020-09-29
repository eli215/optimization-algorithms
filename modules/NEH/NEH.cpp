#include "NEH.h"
#include <algorithm>
#include <unordered_map>

/// @brief Default NEH constructor.
/// @return A default initialized NEH object.
NEH::NEH()
{
	this->processingTimes = std::vector<std::vector<double>>();
	this->numJobs = 0;
	this->numMachines = 0;
	this->solution = std::numeric_limits<double>::max();
}

/// @brief Paramaterized NEH constructor which takes a vector of vectors containing job-machine processing time values.
/// @param processingTimes The FSS problem, in the form of a table processing times. Format: p[job][machine]
/// @return An NEH object initialized with a FSS problem.
NEH::NEH(std::vector<std::vector<double>> processingTimes)
{
	this->processingTimes = processingTimes;
	this->numJobs = processingTimes.size();
	this->numMachines = processingTimes[0].size();
	this->solution = std::numeric_limits<double>::max();
}

/// @brief Carry out steps 1 & 2 of the NEH heuristic as set-up.
void NEH::init()
{
	std::vector<std::vector<double>> sortedProcessingTimes(numJobs, std::vector<double>(numMachines));
	std::vector<std::pair<int, double>> totProcTime(numJobs);		// initialized with 0

	for (int j = 0; j < numJobs; j++)
	{
		totProcTime[j] = std::make_pair(j, 0.0);		// pair[0] = original job index

		for (int m = 0; m < numMachines; m++)
		{
			totProcTime[j].second += processingTimes[j][m];		// pair[1] = total job processing time
		}
	}

	// SORT JOBS BY TOTAL PROCESSING TIME IN DESCENDING ORDER
	std::sort(totProcTime.begin(), totProcTime.end(), [](auto& left, auto& right)	// sort jobs by processing  time
	{
		return left.second > right.second;		// use '>' for descending order)		
	});

	for (int j = 0; j < numJobs; j++)
	{
		int originalJobInd = totProcTime[j].first;
		sortedProcessingTimes[j].swap(processingTimes[originalJobInd]);	// O(1) swap by reference into sorted position
	}

	// FIND SHORTEST MAKESPAN ORDERING OF JOBS 1 & 2
	double makespan1 = partialMakespan(sortedProcessingTimes, 2);
	sortedProcessingTimes[0].swap(sortedProcessingTimes[1]);		// swap job 1 and job 2
	double makespan2 = partialMakespan(sortedProcessingTimes, 2);

	if (makespan1 < makespan2)
	{
		sortedProcessingTimes[0].swap(sortedProcessingTimes[1]);		// swap back if original order was better
	}

	processingTimes = sortedProcessingTimes;	// update processingTimes
}

/// @brief Carry out step 3 of the NEH heuristic, determining which job sequence permutation has minimal makespan.
/// @return The result of the NEH heuristic; a minimal makespan value.
double NEH::run()
{
	init();		// add ordering of jobs 1 and 2 here (use min function? or just pass L = 2 into makespan func)
	std::vector<std::vector<double>> p = processingTimes;

	for (int L = 3; L < numJobs; L++)
	{
		int bestLposition = 0;
		double bestMakespan = std::numeric_limits<double>::max();
		int jobL_curInd = L - 1;		// track current index of job L as we move it around

		for (int i = 0; i < L; i++)
		{
			moveVectorElement(p, jobL_curInd, i);
			jobL_curInd = i;
			double makespan = partialMakespan(p, L);

			if (makespan < bestMakespan)
			{
				bestMakespan = makespan;
				bestLposition = i;
			}
		}

		moveVectorElement(p, jobL_curInd, bestLposition);		// when finished, move job L to its optimal position
	}

	solution = partialMakespan(p, numJobs);
	return solution;
}

/// @brief Calculate makespan, given a subsequence of jobs.
/// @param p A vector of all processing times for the current problem.
/// @param L The length of the subsequence, starting with the first job. Note: the job at index L is not included in the subsequence.
/// @return The makespan of the given subsequence of jobs.
double NEH::partialMakespan(std::vector<std::vector<double>>& p, int L)
{
	std::vector<std::vector<double>> C(L, std::vector<double>(numMachines));		// completion times

	C[0][0] = p[0][0];		// completion time of C_1,1 is simply its processing time

	// FORMULA 1 - Calculate job 1 completion times for all machines
	for (int i = 1; i < numMachines; i++)
	{
		C[0][i] = C[0][i - 1] + p[0][i];	// comp time of last mach + proc time of this mach
	}

	// FORMULA 2 - Calculate machine 1 completion times for remaining jobs in subsequence
	for (int k = 1; k < L; k++)
	{
		C[k][0] = C[k - 1][0] + p[k][0];
	}

	// FORMULA 3 - Calculate completion times for all remaining jobs & machines 
	for (int i = 1; i < L; i++)		// for each job in subsequence
	{
		for (int k = 1; k < numMachines; k++)		// for each machine
		{
			C[i][k] = std::max(C[i - 1][k], C[i][k - 1]) + p[i][k];
		}
	}

	return C[L - 1][numMachines - 1];		// makespan is the accumulated result of all completion times for this flow shop
}

/// @brief Move an element within a vector using repeated swaps. O(n)
/// @param v The containing vector within which we are shifting elements
/// @param initialInd The index of the element being moved.
/// @param newInd The index the selected element is being moved to.
void NEH::moveVectorElement(std::vector<std::vector<double>>& v, int initialInd, int newInd)
{
	bool increasing = (initialInd < newInd);

	for (int i = initialInd, c = std::abs(newInd - initialInd); c > 0; c--, i += (increasing) ? 1 : -1)
	{
		int swap_index = (increasing) ? i + 1 : i - 1;
		v[i].swap(v[swap_index]);		// swap vectors by reference O(1)
	}
}


