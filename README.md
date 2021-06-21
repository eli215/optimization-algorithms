# Optimization Algorithms

This is a collection of optimization problems that were originally part of my coursework.
My goal now is to expand upon the algorithms, improve code modularity, add more testing, and add data analysis and visualization of the results.
  
Status: in progress (as of 2021-06)

## Contents

[Problem](https://github.com/eli215/optimization-algorithms/tree/main/Problem)
- defines standard benchmark functions
- represents the target of an optimization problem

[BlindSearch](https://github.com/eli215/optimization-algorithms/tree/main/BlindSearch)
- implements a blind search/random walk algorithm
- requires a Problem instance as its target

[LocalSearch](https://github.com/eli215/optimization-algorithms/tree/main/LocalSearch)
- implements a local search algorithm
- requires a Problem instance as its target

[DifferentialEvolution](https://github.com/eli215/optimization-algorithms/tree/main/DifferentialEvolution)
- implements a differential evolution algorithm
- requires a Problem instance as its target

[NEH](https://github.com/eli215/optimization-algorithms/tree/main/NEH)
- implements the NEH heuristic for solving flow shop sequencing problems
- requires FSS problem instance input via CSV file