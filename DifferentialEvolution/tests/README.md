# DifferentialEvolution testing

This program runs a differential evolution algorithm over a number of the 18 benchmark functions from Project 1,
printing the results to output files.

Class descriptions:

- main: Contains driver code to exercise the functionality of each of the below classes, performing loops based upon how many experiments are specified by user input.

- Problem: Contains static implementations of 18 benchmark functions, stores defining info about each individual problem when instantiated. 
Can generate random solution vectors.

- DifferentialEvolution: Contains an implementation of the Differential Evolution optimization algorithm. Requires a Problem object and other parameters to run; uses 
the Problem.generateRandomSolution() method to generate its initial population. Utilizes the DE/rand/1/bin strategy. Must call run() after initializing to run; returns 
a solution vector, though solution and fitness are stored in class fields as well.

- FileHandler: Handles input file reading and writing results to output files.
Default input file name: "input.txt"
Default Differential Evolution output file name(s): "f#_DE_results.csv" where # is a function ID number.

Input file format template:

1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18	// line 1: list of objective functions to be tested  
50		//line 2: number of experiments  
100		//line 3: number of generations  
200		//line 4: population size (solutions per population)  
30		//line 5: dimensions per solution  
0.8		//line 6: value of F (mutation constant)  
0.5		//line 7: value of CR (crossover probability constant)  
		//line 8: newline divider (required)  
-512 512	//line 9: objective function #1 solution bounds [min, max]  
-100 100	//line 10: objective function #2 solution bounds [min, max]  
-100 100	//... etc. for all 18 objective functions, up to line 26  
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

Notes:  
- Must delete comments before using this example.
- FileHandler expects 18 lines of function bounds, do not exclude any.
- Values must be separated by spaces.
- The above format is strict; deviating from it will result in undesired behavior.