#include "Problem.hpp"

Problem::Problem()
{
    this->functionId = 0;
    this->dimension = 0;
    this->bounds = {0, 0};
    this->objFunc = nullptr;

    this->RANDOM_SEED = 0;
    this->mtEngine = std::mt19937();
}

/// @brief Parameterized Problem constructor for a specific problem function.
/// @param functionId The 0-based ID/index of the problem function.
/// @param lowerBound The INCLUSIVE lower bound for solution vector values.
/// @param upperBound The INCLUSIVE upper bound for solution vector values.
/// @param dimension The specified solution vector dimension value.
/// @return initialized Problem object.
Problem::Problem(int functionId, int dimension, std::array<double, 2> bounds)
{
	this->functionId = functionId;
	this->dimension = dimension;
	this->bounds = bounds;
	this->objFunc = functions[functionId];

	std::random_device rd{};
	this->RANDOM_SEED = rd();		// generate random seed
	this->mtEngine = std::mt19937(RANDOM_SEED);
}

/// @brief Generate a pseudo-random solution vector, where dimension and solution space correspond to this Problem object.
/// @param mtEng The mt19937 object used to generate random values.
/// @param bounds The INCLUSIVE solution space bounds. [0] = lower bound, [1] = uppder bound.
/// @return A pseudo-random solution vector.
std::vector<double> Problem::generateSolutionVector(std::mt19937 mtEng, int dimension, std::array<double, 2> bounds)
{
	std::vector<double> vector(dimension);		// Allocate vector of given dimension size
	double range = bounds[1]- bounds[0];		// Calculate statistical range (upper - lower)
    auto realDist = std::uniform_real_distribution<double>(0.0, 1.0);   // Real number distribution over range [0.0, 1.0].

	for (int i = 0; i < dimension; i++)
	{
		vector[i] = bounds[0] + (realDist(mtEng) * range);  // Generate vector of random values within given solution space
	}

	return vector;
}

/// @brief implementation of Schwefel's benchmark function
/// @param x input vector of doubles
/// @return double result of the function
double Problem::schwefel(std::vector<double>& x)		// #1
{
	int n = x.size();	// # of dimensions
	double sum = 0;

	for (int i = 0; i < n; i++)		// for dimension 1 to n
	{
		sum += x[i] * sin(sqrt(fabs(x[i])));
	}

	return (418.9829 * n) - sum;
}

/// @brief implementation of De Jong 1 benchmark function
/// @param x input vector of doubles
/// @return double result of the function
double Problem::deJong1(std::vector<double>& x)		// #2
{
	int n = x.size();
	double sum = 0;

	for (int i = 0; i < n; i++)
	{
		sum += pow(x[i], 2);
	}

	return sum;
}

/// @brief implementation of Rosenbrock's Saddle benchmark function
/// @param x input vector of doubles
/// @return double result of the function
double Problem::rosenbrocksSaddle(std::vector<double>& x)		// #3
{
	int n = x.size();
	double sum = 0;

	for (int i = 0; i < n - 1; i++)
	{
		sum += 100 * pow(pow(x[i], 2) - x[i + 1], 2) + pow(1 - x[i], 2);
	}

	return sum;
}

/// @brief implementation of Rastrigin benchmark function
/// @param x input vector of doubles
/// @return double result of the function
double Problem::rastrigin(std::vector<double>& x)		// #4
{
	int n = x.size();
	double sum = 0;

	for (int i = 0; i < n; i++)
	{
		sum += pow(x[i], 2) - 10 * cos(2 * M_PI * x[i]);
	}

	return (n * 10.0) + sum;
}

/// @brief implementation of Griewangk benchmark function
/// @param x input vector of doubles
/// @return double result of the function
double Problem::griewangk(std::vector<double>& x)		// #5
{
	int n = x.size();
	double sum = 0;
	double product = 1;

	for (int i = 1; i <= n; i++)		// i = 1 because value of i is used in formula
	{
		sum += pow(x[i - 1], 2) / 4000;
		product *= cos(x[i - 1] / sqrt(i));
	}

	return 1 + sum - product;
}

/// @brief implementation of Sine Envelope Sine Wave benchmark function
/// @param x input vector of doubles
/// @return double result of the function
double Problem::sineEnvelopeSineWave(std::vector<double>& x)		// #6
{
	int n = x.size();
	double sum = 0;
	double expr;

	for (int i = 0; i < n - 1; i++)
	{
		expr = pow(x[i], 2) + pow(x[i + 1], 2);		// store repeated expression
		sum += 0.5 + (pow(sin(expr - 0.5), 2) / pow(1 + 0.001 * expr, 2));
	}

	return -1 * sum;
}

/// @brief implementation of Stretched V Sine Wave benchmark function
/// @param x input vector of doubles
/// @return double result of the function
double Problem::stretchedVsineWave(std::vector<double>& x)		// #7
{
	int n = x.size();
	double sum = 0;
	double expr;

	for (int i = 0; i < n - 1; i++)
	{
		expr = pow(x[i], 2) + pow(x[i + 1], 2);		// store repeated expression
		sum += pow(expr, 1 / 4.0) * pow(sin(50 * pow(expr, 1 / 10.0)), 2) + 1;
	}

	return sum;
}

/// @brief implementation of Ackley's One benchmark function
/// @param x input vector of doubles
/// @return double result of the function
double Problem::ackleyOne(std::vector<double>& x)		// #8
{
	int n = x.size();
	double sum = 0;
	double e_0pt2 = exp(0.2);		// store to avoid recalculation

	for (int i = 0; i < n - 1; i++)
	{
		sum += (1 / e_0pt2) * sqrt(pow(x[i], 2) + pow(x[i + 1], 2)) + 3 * (cos(2 * x[i]) + sin(2 * x[i + 1]));
	}

	return sum;
}

/// @brief implementation of Ackley's Two benchmark function
/// @param x input vector of doubles
/// @return double result of the function
double Problem::ackleyTwo(std::vector<double>& x)		// #9
{
	int n = x.size();
	double sum = 0;
	double e = exp(1.0);

	for (int i = 0; i < n - 1; i++)
	{
		sum += 20 + e - (20 / exp(0.2 * sqrt((pow(x[i], 2) + pow(x[i + 1], 2)) / 2)))
			- exp(0.5 * (cos(2 * M_PI * x[i]) + cos(2 * M_PI * x[i + 1])));
	}

	return sum;
}

/// @brief implementation of Egg Holder benchmark function
/// @param x input vector of doubles
/// @return double result of the function
double Problem::eggHolder(std::vector<double>& x)		// #10
{
	int n = x.size();
	double sum = 0;

	for (int i = 0; i < n - 1; i++)
	{
		sum += -x[i] * sin(sqrt(fabs(x[i] - x[i + 1] - 47))) - (x[i + 1] + 47) * sin(sqrt(fabs(x[i + 1] + 47 + (x[i] / 2))));
	}

	return sum;
}

/// @brief implementation of Rana benchmark function
/// @param x input vector of doubles
/// @return double result of the function
double Problem::rana(std::vector<double>& x)		// #11
{
	int n = x.size();
	double sum = 0;
	double expr1;
	double expr2;

	for (int i = 0; i < n - 1; i++)
	{
		expr1 = sqrt(fabs(x[i + 1] - x[i] + 1));
		expr2 = sqrt(fabs(x[i + 1] + x[i] + 1));
		sum += x[i] * sin(expr1) * cos(expr2) + (x[i + 1] + 1) * cos(expr1) * sin(expr2);
	}

	return sum;
}

/// @brief implementation of Pathological benchmark function
/// @param x input vector of doubles
/// @return double result of the function
double Problem::pathological(std::vector<double>& x)		// #12
{
	int n = x.size();
	double sum = 0;

	for (int i = 0; i < n - 1; i++)
	{
		sum += 0.5 + (pow(sin(sqrt(100 * pow(x[i], 2) + pow(x[i + 1], 2))), 2) - 0.5)
			/ (1 + 0.001 * pow((pow(x[i], 2) - 2 * x[i] * x[i + 1] + pow(x[i + 1], 2)), 2));
	}

	return sum;
}

/// @brief implementation of Michalewicz benchmark function
/// @param x input vector of doubles
/// @return double result of the function
double Problem::michalewicz(std::vector<double>& x)		// #13
{
	int n = x.size();
	double sum = 0;

	for (int i = 0; i < n; i++)
	{
		sum += sin(x[i]) * pow(sin((i * pow(x[i], 2)) / M_PI), 20);
	}

	return -1 * sum;
}

/// @brief implementation of Masters Cosine Wave benchmark function
/// @param x input vector of doubles
/// @return double result of the function
double Problem::mastersCosineWave(std::vector<double>& x)		// #14
{
	int n = x.size();
	double sum = 0;
	double expr;

	for (int i = 0; i < n - 1; i++)
	{
		expr = pow(x[i + 1], 2) + (0.5 * x[i] * x[i + 1]) + pow(x[i], 2);
		sum += exp(-1 / 8.0 * expr) * cos(pow(expr, 1 / 4.0));
	}

	return sum;
}

/// @brief implementation of Quartic benchmark function
/// @param x input vector of doubles
/// @return double result of the function
double Problem::quartic(std::vector<double>& x)		// #15
{
	int n = x.size();
	double sum = 0;

	for (int i = 1; i <= n; i++)		// i = 1 because value of i is used in formula
	{
		sum += i * pow(x[i - 1], 4);
	}

	return sum;
}

/// @brief implementation of Levy benchmark function
/// @param x input vector of doubles
/// @return double result of the function
double Problem::levy(std::vector<double>& x)		// #16
{
	int n = x.size();
	double sum = 0;
	double wi;
	double wn = 1 + (x[n - 1] - 1) / 4.0;
	double w1 = 1 + (x[0] - 1) / 4.0;

	for (int i = 0; i < n - 1; i++)
	{
		wi = 1 + (x[i] - 1) / 4.0;
		sum += pow(wi - 1, 2) * (1 + 10 * pow(sin(M_PI * wi + 1), 2)) + pow(wn - 1, 2) * (1 + pow(sin(2 * M_PI * wn), 2));
	}

	return pow(sin(M_PI * w1), 2) + sum;
}

/// @brief implementation of Step benchmark function
/// @param x input vector of doubles
/// @return double result of the  function
double Problem::step(std::vector<double>& x)		// #17
{
	int n = x.size();
	double sum = 0;

	for (int i = 0; i < n - 1; i++)
	{
		sum += pow(fabs(x[i]) + 0.5, 2);
	}

	return sum;
}

/// @brief implementation of Alpine benchmark function
/// @param x input vector of doubles
/// @return double result of the function
double Problem::alpine(std::vector<double>& x)		// #18
{
	int n = x.size();
	double sum = 0;

	for (int i = 0; i < n - 1; i++)
	{
		sum += fabs(x[i] * sin(x[i]) + 0.1 * x[i]);
	}

	return sum;
}
