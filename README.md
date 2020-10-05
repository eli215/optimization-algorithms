# Optimization Algorithms

This is a collection of optimization problems that were originally part of my coursework.
My goal now is to expand upon the algorithms, improve code modularity, and improve testing.


## Contents

Problem
- defines standard benchmark functions
- represents the target of an optimization problem

BlindSearch
- implements a blind search/random walk algorithm
- requires a Problem instance as its target

LocalSearch
- implements a local search algorithm
- requires a Problem instance as its target

DifferentialEvolution
- implements a differential evolution algorithm
- requires a Problem instance as its target

NEH
- implements the NEH heuristic for solving flow shop sequencing problems
- requires FSS problem instance input via CSV file