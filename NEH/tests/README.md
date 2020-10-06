# NEH testing

This program uses an implementation of the NEH heuristic to solve all 120 of Taillaird's flow shop sequencing problem instances.

Link to Taillard's instances data:
http://mistic.heig-vd.ch/taillard/problemes.dir/ordonnancement.dir/ordonnancement.html
  
Classes:

- main: Contains driver code to exercise the functionality of the NEH class, also making use of the FileHandler class in order load sample FSS problems into the program & print the results.

- NEH: Contains an implementation of the NEH heuristic. Constructor requires a vector<vector<double>> object containing the processing times for each individual [job][machine] pair. 
Eg. 
The value at vector element v[0][0] --> processing time for job 1, machine 1.  
The value at vector element v[1][0] --> processing time for job 2, machine 1.  
The value at vector element v[n-1][m-1] --> processing time for job n, machine m.  
The private method init() is called only by run(), and carries out steps 1 and 2 as listed above. The public method run(), after calling init(), carries out step 3 of the heuristic, then returns the resulting minimal makespan value.

- FileHandler: Handles input file reading and output file writing. 
Input files are read from a directory named "DataFiles", which must exist in the same directory as the executable. This is where all of the Taillard problem instance files have been placed.
These input files must be formatted as follows:  
line 1 = "m n" where m = # of machines, n = # of jobs  
lines 2 to m+1 = a list of n space-separated values, where each value corresponds to the processing time for that machine and job index.  

Output files will be placed in a new directory named "Results", which will be created if it doesn't already exist. A separate output file is created for each unique (# machines, # jobs) combination.  

Default output file name template = "{#M}M{#J}J_NEH_results.csv", where {#M} and {#J} are replaced by the values for # of machines and jobs, respectively.
Eg.
5M20J_NEH_results.csv
5M50J_NEH_results.csv
20M50J_NEH_results.csv