# NEH Heuristic
The NEH heuristic (Nawas, Enscore, and Ham, 1983) was for many years considered the best heuristic for solving the permutation flow shop problem. This variation of the flow shop problem has a fixed processing order (M_1, M_2, ..., M_m), so the goal is to find the job sequence which minimizes the makespan. This algorithm has a time complexity in O(mn3), where m = # machines and n = # jobs.

The NEH heuristic consists of three steps: 
1. For each job find the total processing time over all machines, then sort the jobs in decreasing order of these sums.
1. Order the first two jobs such that their partial makespan is minimal.
1. Beginning with this two-job subsequence, add all remaining jobs one at a time, each into the position which minimizes partial makespan. 








