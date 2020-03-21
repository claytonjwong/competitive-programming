## [Week 1: Programming Competitions](1_programming_competitions)
### Key Concepts
* Know various strategies for inventing test cases and testing programs
* Understand what programming competitions and algorithmic problems are, what's the difference compared to other forms of programming
* Learn about various platforms dedicated to competitive programming, and what opportunities they offer

### Resources
1. [Competitions](1_programming_competitions/docs/competitions.pdf)
2. [Testing](1_programming_competitions/docs/testing.pdf)

### Assignments
0. [Inventing Tests](1_programming_competitions/README.md#inventing-tests)
1. [Addition and Subtraction](1_programming_competitions/README.md#addition-and-subtraction)
2. [Erasing Maximum](1_programming_competitions/README.md#erasing-maximum)
3. [Increment](1_programming_competitions/README.md#increment)
4. [Straight Flush](1_programming_competitions/README.md#straight-flush)

## [Week 2: Correctness First](2_correctness_first)
### Key Concepts
* Deduce simple upper bounds on a solution's running time and decide if it's fast enough for a given time limit
* Implement brute force solutions with basic recursive backtracking
* Understand the connection between code structure and the logic behind it

### Resources
1. **[Structuring Code](2_correctness_first/docs/1_structuring_code/structuring_code.pdf)**
2. **Brute-Force Solutions:** Always Conceptually Correct (but extremely slow)
	* [Intuitive "Proofs" are Wrong](2_correctness_first/docs/2_brute_force_solutions/proofs.pdf)
	* [Defining Solution Set](2_correctness_first/docs/2_brute_force_solutions/solutionset.pdf)
		* Search Space (ie. set A)
			* Find an element of a set A which satisfies some property
			* Find an element of a set A which minimizes/maximizes an objective function
			* Find the number of elements of a set A satisfying some property
	* [Recursive Backtracking](2_correctness_first/docs/2_brute_force_solutions/backtracking.pdf): Code equivalent to N nested for-loops
		* Recipe for developing a brute-force solution:
			* Identify the search space for a problem
			* Design a method to enumerate all elements of the search space
3. **Time Complexity:** Estimating the number of unit operations in an algorithm
	* [Worst Cases](2_correctness_first/docs/3_time_complexity/worst_average.pdf)
	* [Big-O Notation](2_correctness_first/docs/3_time_complexity/bigO.pdf)
		* Always calculate the Big-O asymptotic bound before implementation
	* [From Theory to Practice: How to make a solution faster](2_correctness_first/docs/3_time_complexity/time_final.pdf)
		* Focus optimizations on bottlenecks only
		* First optimize asymptotically (major gain), if and only if this fails, then further optimize constants (minor gain)

### Assignments
0. [Quiz](2_correctness_first/README.md#quiz)
1. [The Cheapest Permutation](2_correctness_first/README.md#the-cheapest-permutation)
