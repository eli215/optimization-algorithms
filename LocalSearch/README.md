# Local Search

The Local Search algorithm is a search method which takes an initial solution input, generates a set of neighboring solutions, and chooses the best out of these neighbors. The chosen improvement is used as the input for the next iteration, and this process is repeated until we reach a point where the input solution is superior to all of its neighbors (or until a specified maximum number of iterations is reached).
  

An exhaustive local search via gradient descent is very thorough, however extremely resource intensive, and not well suited for large data sets. A more efficient alternative is stochastic gradient descent, with which initial solutions are randomly generated. Rather than using all possible data points to find the optimal solution, we use a smaller set of random data points to find a close approximation of the optimal solution.