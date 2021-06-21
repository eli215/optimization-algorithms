#pragma once

#include <vector>
#include <array>
#include <random>

/// @brief Represents the subject of an optimization problem. A Problem object corresponds to a specific
/// objective function, with a specific solution dimension and solution space.
/// All objective/benchmark functions are defined statically.
class Problem
{

public:

	/******************************
	 * Static Benchmark Functions *
	 ******************************/
	static double schwefel(std::vector<double>& input);
	static double deJong1(std::vector<double>& input);
	static double rosenbrocksSaddle(std::vector<double>& input);
	static double rastrigin(std::vector<double>& input);
	static double griewangk(std::vector<double>& input);
	static double sineEnvelopeSineWave(std::vector<double>& input);
	static double stretchedVsineWave(std::vector<double>& input);
	static double ackleyOne(std::vector<double>& input);
	static double ackleyTwo(std::vector<double>& input);
	static double eggHolder(std::vector<double>& input);
	static double rana(std::vector<double>& input);
	static double pathological(std::vector<double>& input);
	static double michalewicz(std::vector<double>& input);
	static double mastersCosineWave(std::vector<double>& input);
	static double quartic(std::vector<double>& input);
	static double levy(std::vector<double>& input);
	static double step(std::vector<double>& input);
	static double alpine(std::vector<double>& input);

	static const int NUM_FUNCTIONS = 18;	/**< Number of static benchmark functions defined. */
	static inline int getNumFunctions() { return NUM_FUNCTIONS; };
	typedef double func(std::vector<double>& input);	/**< Define function pointer. Params: vector<double>. Return: double. */
    static std::vector<double> generateSolutionVector(std::mt19937 mtEng, int dimension, std::array<double, 2> bounds);

	static constexpr func* functions[NUM_FUNCTIONS] = {
			Problem::schwefel,
			Problem::deJong1,
			Problem::rosenbrocksSaddle,
			Problem::rastrigin,
			Problem::griewangk,
			Problem::sineEnvelopeSineWave,
			Problem::stretchedVsineWave,
			Problem::ackleyOne,
			Problem::ackleyTwo,
			Problem::eggHolder,
			Problem::rana,
			Problem::pathological,
			Problem::michalewicz,
			Problem::mastersCosineWave,
			Problem::quartic,
			Problem::levy,
			Problem::step,
			Problem::alpine
	};    /**< An enumeration of all benchmark function pointers. */

    /*******************************
     * Non-static fields & methods *
     *******************************/
	Problem(int functionId = 0, double lowerBound = 0, double upperBound = 0, int dimension = 0);// , int maxIterations = 0);
	std::vector<double> generateRandomVector();

	/// @brief Generate random real number in range [0.0, 1.0].
	/// @return random double value in range [0.0, 1.0].
	inline double randReal_0to1() { return realDist(mtEngine); };

    // Getters
    inline int getFunctionId() { return functionId; };
	inline double getLowerBound()	{ return lowerBound; };
	inline double getUpperBound()	{ return upperBound; };
    inline int getDimension() { return dimension; };
    // inline func* getObjFunc() { return objFunc; };
	inline std::mt19937 getMtEngine() { return mtEngine; };
    inline unsigned long getRandomSeed() { return RANDOM_SEED; };

private:

	int functionId;		/**< The 0-based ID of the problem function. Use this ID as a Problem::functions[] index to retrieve the corresponding function pointer. */
	double lowerBound;		/**< The INCLUSIVE lower bound for solution vector values. */
	double upperBound;		/**< The INCLUSIVE upper bound for solution vector values. */
	int dimension;		/**< The specified solution vector dimension value. */
	
	// double range;			/**< The statistical range for solution vector values (upperBound - lowerBound). */
	// double fpOffset;		/**< The floating-point offset for this range. Allows bounds to be real numbers. */

	unsigned long RANDOM_SEED;	/**< The seed used for this instance of mt19937-- allows for reproducible results. */
	std::mt19937 mtEngine;	/**< Mersenne-Twister pseudo-random number generator. */
	std::uniform_real_distribution<double> realDist; /**< Real number distribution over the range [0.0, 1.0]. */
};

