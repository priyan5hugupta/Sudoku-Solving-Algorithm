# Sudoku-Solving-Algorithm
1. Project Title  
Sudoku Solver Algorithms  
  
2. Abstract  
The research evaluates different Sudoku-solving algorithms based on their time-based complexity. It evaluates the performance of the algorithms Breadth-First Search (BFS), Depth-Limited Search (DLS), Bit Mask, and Cross Hatching. The study evaluates the time it takes each algorithm to solve a problem, showing its flexibility to differing complexities. To understand the time complexity characteristics of the algorithms, they are subjected to a variety of Sudoku puzzles. The study's goal is to provide a more detailed understanding of each algorithm's performance under time limitations, helping developers in choosing acceptable solutions. The results help to optimise algorithms and motivate future advancements in puzzle-solving approaches and computational strategies. 
 
3. Introduction  
Sudoku, a puzzle game invented by Swiss mathematician Leonhard Euler, is a famous and difficult puzzle game. It originated in Japan in the 1980s and has since become common in newspapers, publications, and digital platforms around the world. The game's basic principles are simple, making it fair to players of all capacity levels. The game is played on a 9x9 grid separated into nine 3x3 subgrids, with the goal of filling the entire grid with numbers ranging from 1 to 9. Every digit from 1 to 9 must be present in every row, column, and 3x3 subgrid, with no repeat. 
 
The game begins with a half- completed puzzle containing pre-filled numbers, known as "givens" or "clues," as the beginning point for solving. Numbers may not be duplicated in any row, column, or 3x3 subgrid, and each digit must be distinct within its own row, column, and subgrid. The puzzle is considered solved when the complete grid is filled in accordance with the rules. 
 
 
 
 
 
 
 
 
 
 
4. Literature Review  
This literature review examines the time efficiency of four prominent Sudoku-solving algorithms: BreadthFirst Search (BFS), Depth-Limited Search (DLS), Bit Mask, and Cross Hatching 
I) 	Breadth-First Search (BFS) and Depth-Limited Search (DLS): BFS and DLS are traditional search methods that are commonly used to solve complex issues. Existing literature, such as Knuth's (2000) work, has investigated their applicability in Sudoku solving. DLS travels down a branch before backtracking, whereas BFS explores the puzzle area level by level. These algorithms give the foundation for understanding Sudoku-solving tactics. Steps of the Breadth-First Search (BFS) Algorithm 
1.	Initialization:  
•	Place the initial node in a queue. 
•	Add a visit to the initial node. 
2.	BFS Iteration: - 
•	While the queue is not empty: 
•	Dequeue a node from the front of the queue. 
•	Process the node (perform any desired operation). 
•	Enqueue all unvisited neighbors of the node. 
3.	Termination: 
•	Continue steps 2 until the queue is empty. 
Example: 
Suppose we have the following graph: 
   A 
  / \ 
 B   C 
 |   | 
 D   E 
1.	Starting with node A: 
2.	Enqueue A, mark A as visited. 
3.	Dequeue A, process A. 
4.	Enqueue B and C. 
5.	Dequeue B, process B. 
6.	Enqueue D. 
7.	Dequeue C, process C. 
8.	Enqueue E. 
9.	Dequeue D, process D 10. Dequeue E, process E. 
The order of processing in this example would be A, B, C, D, E, illustrating the breadth-first exploration. 
 
Steps of the Depth-Limited Search (DLS) Algorithm: 
1.	Initialization: 
•	Set the initial state as the current state. 
•	Set the depth limit to a predefined value. 
2.	Depth-Limited Search Function: 
•	Implement a recursive or iterative depth-limited search function. 
3.	Recursive Version (Optional): 
•	If using recursion, define a function that takes the current state, current depth, and depth limit as parameters. 
4.	Base Cases: 
•	Check if the current state is the goal state. 
•	If true, return a solution or mark the goal state as reached. 
•	Check if the current depth exceeds the depth limit. 
•	If true, terminate the search at this branch. 
5.	Expansion: 
•	Generate all possible successor states from the current state. 
•	Apply any domain-specific pruning or filtering based on the problem. 
6.	Recursive Exploration: 
•	For each successor state: 
•	Recursively call the DLS function with the successor state, increased depth, and the same depth limit. 
7.	Backtracking: 
•	If the goal is not found in the current branch, backtrack to the previous state. 
8.	Depth-Limited Search Call: 
•	Call the depth-limited search function with the initial state, initial depth (usually 0), and the predefined depth limit. 
9.	Solution Handling: 
•	If a solution is found, handle and present the solution as needed. 
10.	Iteration (Optional): 
•	If using an iterative version, repeat the process with an increased depth limit until a solution is found or the entire space is explored. 
11.	Termination: 
•	Terminate the search when the entire search space is explored or when the solution is found. 
 
Example: 
Suppose we have the following graph: 
 
 
Let's say we want to find the node with the value 'L' using DLS. The depth limit is set to 2. 
Steps: 
•	Start at the root node 'A'. 
•	Set the depth limit to 2. 
•	Implement a depth-limited search function. 
•	Call the DLS function with the initial state 'A', depth 0, and depth limit 2. 
•	Explore 'A' and move to its children, 'B', 'C', and 'D'. 
•	Depth 1: o Explore 'B', 'C', and 'D'. o For 'B', explore 'E' and 'F'. 
o	For 'C', explore 'G'. 
o	For 'D', explore 'H' and 'I'. 
• Depth 2: 
o For 'E', 'F', 'G', 'H', and 'I', explore their children. 
•	The goal node 'L' is found under node 'F' at depth 2. 
•	Return the path from the root to the goal node ('A' -> 'B' -> 'F' -> 'K' -> 'L'). 
 
II)	Bit Mask: Bit masking is a technique that improves the encoding and manipulation of cell values in Sudoku problems. Norvig (2009) and others' research has highlighted the efficiency advantages realised by using bitwise operations. Bit masking reduces memory usage and speeds up operations, adding to faster solving times when compared to traditional approaches. 
Bitmasking is a technique used in Sudoku-solving algorithms to represent and manipulate the possible values (candidates) for each cell efficiently. Instead of using separate data structures for each possible value, bitwise operations are employed to store and update the candidates in a compact manner. 
 
The following steps outline the bitmasking algorithm in Sudoku solving: 
1.	Initialization:  
•	Create a bitmask for each cell in the Sudoku grid to show the various possible values. 
Initially, the bitmask contains all digits from 1 to 9. 
2.	Elimination of Candidate Values:  
•	Traverse through the Sudoku puzzle's first clues. 
•	Update the bitmask for each filled cell to represent the single acceptable value by setting only one bit and clearing the rest. 
3.	Propagation:  
•	Use constraint propagation to update candidate values iteratively based on the elimination of values in other cells within the same row, column, or 3x3 subgrid. 
4.	Bitwise Operations: 
•	Use bitwise operations such as OR, AND, and NOT to update and change the bitmask for each cell efficiently. 
•	To include a candidate value, the OR operation is employed. 
•	The AND operator is used to eliminate out a candidate value. 
•	The NOT operation is used to toggle the bits that indicate potential values. 
5.	Single Candidate Identification:  
•	Identify cells in which only one candidate value exists after constraint propagation.  
•	These cells can be filled with confidence with the remaining value. 
6.	Backtracking: 
•	If constraint propagation alone does not solve the puzzle, turn to backtracking. 
•	Choose the cell with the minimum candidate values and attempt each option recursively. 
•	If a contradiction is discovered, back to the previous state and investigate other options. 
7.	Finishing: 
•	Repeat steps 3-6 until the Sudoku puzzle is completed.\ 
 
III)	Cross Hatching: Inspired by constraint propagation, cross hatching involves gradually removing possible values based on row and column interactions. Berthier et al. (2013) first described this strategy, highlighting its efficacy in reducing the search space and speeding up puzzle solution. Cross Hatching helps to resolve Sudoku puzzles with greater effectiveness, especially when alternative algorithms are challenged. 
Cross hatching is a solving technique in Sudoku that involves iteratively eliminating candidate values from cells within a row or column based on the presence of values in other cells within the same row or column. This technique leverages constraints to narrow down the possibilities in a systematic manner. 
Here are the steps involved in solving a Sudoku puzzle using cross hatching: 
1.	Initialization:  
•	Begin with a completely or partially filled Sudoku puzzle. 
2.	Assign Candidate Value: 
•	Based on the Sudoku rules, assign starting candidate values to each cell. Each cell might initially have numerous possible values. 
3.	Row Cross Hatching: 
•	Examine the filled cells in each row and find the possible values that are present. 
•	Eliminate candidate values that already exist in the filled cells of that row in the vacant cells of that row. 
4.	Column Cross Hatching: 
•	Examine the filled cells in each column and find the possible values that are present. 
•	Eliminate candidate values that already exist in the filled cells of that column in the empty cells of that column. 
5.	Repeat Steps 3 and 4:  
•	Apply cross hatching to rows and columns iteratively until no further elimination is possible. 
6.	Selecting a Single Candidate: 
•	Find cells that have just one candidate value left after cross hatching. These cells can be filled with confidence with the remaining value. 
7.	Cross Hatching - Optional Boxes:  
•	Examine the filled cells in each 3x3 box and determine the possible values that are there. 
•	Remove candidate values from the empty cells of that box that already exist in the filled cells of the same box. 
8.	Repeat Steps 3, 4, and 7: 
•	Apply cross hatching to rows, columns, and boxes iteratively until no further elimination is possible. 
9.	Retrace your steps (if necessary):  
•	If cross hatching alone does not solve the puzzle, go to backtracking. 
•	Select the cell with the fewest possible values and attempt each alternative iteratively. 
•	If a contradiction is discovered, return to the previous state and investigate other options. 
10.	Puzzle Completion:  
•	Continue the cross hatching and backtracking process until the Sudoku puzzle is completed. 
 
IV)	Comparison Studies: Several comparison studies have been carried out to evaluate the performance of various Sudoku-solving algorithms. Goh and Lim (2015) conducted a comparison of search algorithms, including BFS and DLS, focusing on their time-based complexities. Furthermore, Smith (2017) investigated the benefits of bitwise operations in Sudoku solution, suggesting the use of Bit Mask in algorithmic techniques. 
V)	Practical Applications: The literature goes into the practical uses of these algorithms in addition to theoretical comparisons. The adaptability of Sudoku-solving algorithms to real-time problem generation and adjustment has been studied by researchers such as Garcia and Molina (2020), revealing light on their scalability and responsiveness in dynamic circumstances. 
VI)	Challenges and Future Directions: While these algorithms exhibit strengths, challenges persist, and ongoing research explores ways to address them. For instance, the balance between exploration and exploitation in search algorithms remains a subject of interest (Chang et al., 2021), and researchers are actively exploring hybrid approaches to leverage the strengths of multiple algorithms in tandem. 
In conclusion, the literature provides a rich foundation for understanding the comparative analysis of Sudoku-solving algorithms concerning time efficiency. Through the exploration of classic search algorithms, bitwise operations, and constraint propagation techniques, researchers have made significant strides in optimizing solving strategies. The integration of these findings into real-world applications continues to drive advancements in Sudoku-solving algorithms, contributing to the broader landscape of combinatorial problem-solving in artificial intelligence and computer science. 
  
5. Problem Statement  
The goal of the project is to evaluate and analyse the efficiency of several Sudoku-solving algorithms, such as Breadth-First Search, Depth-Limited Search, Bit Masking, and Cross Hatching. Their focus is on analysing their time-based complexity when solving Sudoku problems of varied difficulty levels. This comparison study aims to provide understanding of each algorithm's strengths and limitations, leading the selection of ideal tactics for Sudoku-solving applications.  
 
6. The project's specific goals and tasks include:  
1.	Algorithm Implementation: Implement Breadth-First Search, Depth-Limited Search, Bit Masking, and Cross Hatching Sudoku-solving algorithms. 
2.	Dataset Preparation: Compile a dataset of 100 Sudoku puzzles with varying degrees of complexity. 
3.	Execution Time Measurement: Apply each algorithm to the entire dataset and measure the execution time for solving each puzzle. 
4.	Data Collection: Record and collect the execution time data for each algorithm on all 100 puzzles. 
5.	Statistical Analysis: Analyze the collected data to compare and contrast the execution times of the different algorithms. 
6.	Visualization: Present the results through visualizations such as graphs or charts for a clear comparison. 
7.	Insight Generation: Extract insights into the efficiency and effectiveness of each algorithm based on their execution times. 
8.	Conclusion: Draw conclusions about the relative performance of the Sudoku-solving algorithms with a focus on execution time. 
By systematically comparing these algorithms based on their execution times, the project aims to provide valuable insights into their practical efficiency in solving Sudoku puzzles of varying complexities. 
 
7. Objectives   
The project's objective is to compare Sudoku-solving algorithms such as Breadth-First Search, DepthLimited Search, Bit Masking, and Cross Hatching, with a focus on execution speeds. Time complexities are being evaluated, algorithmic efficiency is being evaluated through 100 Sudoku puzzles, statistical analysis is being conducted, and useful tips are being provided. The research aims to improve understanding of combinatorial problem-solving procedures in the context of Sudoku puzzles and to contribute to algorithmic optimisation. 
