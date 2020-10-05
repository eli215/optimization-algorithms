Author: Eli Storlie
Date: 07/10/2020
CS 471 - Summer 2020
Project 2 - Blind Search

# Blind Search

This program runs a number of searches of the 18 benchmark functions from Project 1, and prints the results into output files. Testing parameters are specified in the input file "input.txt" using the format explained below.

Classes:

main - Contains driver code to exercise the functionality of each of the below classes, performing loops based upon how many iterations are specified by user input.

Problem - Contains static implementations of 18 benchmark functions, stores defining info about each individual problem when instantiated. Contains random solution generation functionality.

BlindSearch - Contains an implementation of the Blind Search algorithm.

LocalSearch - Contains an implementation of the Local Search algorithm which uses stochastic gradient descent.

FileHandler - Handles input file reading and writing results to output files.
Default input file name: "input.txt"
Default Blind Search output file name: "BS_results.csv"
Default LocalSearch output file name: "LS_results.csv"

Default "input.txt" example (must delete comments before using):

10		//line 1 = solution dimension value
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18	//line 2 = list of functions to be tested
30		//line 3 = number of test cases to perform
500		//line 4 = Blind Search max iteration values to perform
0.2		//line 5 = scaling factor for SGD Local Search
0.11		//line 6 = precision factor for SGD Local Search
		//line 7 = required divider line
-512 512	//line 8 = function1 solution space LOWER and UPPER bounds, respectively
-100 100	//line 9 = function2 solution space LOWER and UPPER bounds, respectively
-100 100	//line 10 ... etc, for each of the 18 functions
-30 30
-500 500
-30 30
-30 30
-32 32
-32 32
-500 500
-500 500
-100 100
0 3.14159265358979323846
-30 30
-100 100
-10 10
-100 100
-100 100

//Note: for dimension, BlindSearch max iteration, and scaling factor, you may optionally list out a series of space-separated values to perform these separate tests all at once. However, all the results will still be written to a single output file, so this can get messy.