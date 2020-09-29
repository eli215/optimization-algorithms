#pragma once

#include <iostream>
#include <random>
#include "Project1.h"

class Driver
{
public:

	static const int NUM_FUNCTIONS = 18;								// number of functions being tested
	static const int NUM_DIMENSIONS = 3;								// number of dimensions specified by Project 1
	static constexpr int dimensions[NUM_DIMENSIONS] = { 10, 20, 30 };	// dimension values specified by Project 1
	static const int NUM_CASES_PER_DIMENSION = 30;						// number of test solutions to perform per given dimension

	typedef double func(std::vector<double>& input);					// define function pointer type

	static constexpr func* functions[NUM_FUNCTIONS] = {					// array of function pointers to Project1's functions
		Project1::schwefel,
		Project1::deJong1,
		Project1::rosenbrocksSaddle,
		Project1::rastrigin,
		Project1::griewangk,
		Project1::sineEnvelopeSineWave,
		Project1::stretchedVsineWave,
		Project1::ackleyOne,
		Project1::ackleyTwo,
		Project1::eggHolder,
		Project1::rana,
		Project1::pathological,
		Project1::michalewicz,
		Project1::mastersCosineWave,
		Project1::quartic,
		Project1::levy,
		Project1::step,
		Project1::alpine
	};		

	static constexpr double bounds[NUM_FUNCTIONS][2] = {
		{-512,512} , 		// 1. Schwefel
		{ -100, 100 }, 		// 2. De Jong 1
		{-100, 100},		// 3. Rosenbrock's Saddle
		{-30, 30},			// 4. Rastrigin
		{-500, 500},		// 5. Griewangk
		{-30, 30},			// 6. Sine Envelope Sine Wave
		{-30, 30},			// 7. Stretched V Sine Wave
		{-32, 32},			// 8. Ackley One
		{-32, 32},			// 9. Ackley Two
		{-500, 500},		// 10. Egg Holder
		{-500, 500},		// 11. Rana
		{-100, 100},		// 12. Pathological
		{0, std::_Pi},		// 13. Michalewicz
		{-30, 30},			// 14. Masters’ Cosine Wave
		{-100, 100},		// 15. Quartic
		{-10, 10},			// 16. Levy
		{-100, 100},		// 17. Step
		{-100, 100}			// 18. Alpine
	};

	static const unsigned long RANDOM_SEED = 123456789;		// use a seed for reproducible results
	static std::mt19937 mtEngine;							// Mersenne-Twister pseudo-random number generator
	static std::uniform_int_distribution<int> intDist;		// used to filter random MT output over the desired closed (inclusive) interval
	static std::uniform_real_distribution<double> realDist;	// used to confine random MT output to range [0.0, 1.0]

	double median(std::vector<double> input);

};

