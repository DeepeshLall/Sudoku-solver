# Sudoku-Solver-using-MiniSAT
Description:
====================

SAT solver for Sudoku puzzles.

This program is a sudoku solver that will transform a sudoku puzzle (9x9) into an instance of the NP-complete SAT problem. It will read a sudoku puzzle table and convert it to a set of boolean formulae (used by SAT solvers) to solve the puzzle.

Used minisat SAT solver reference : http://minisat.se/Main.html

Instructions:
====================

Run the following command (assuming minisat is installed on the machine, put all files in the core folder of minisat):

"gcc solver.cpp"

"./a.out"

Contents:
====================

* solver.cpp :
  Needs the input in encode.txt having a 9X9 sudoku that is to be solved. And produces the minisat's output in decode.txt, which is used to produce and flush the solved Sudoku on STDOUT.
  
  - Input : encode.txt
  - Output : decode.txt, STDOUT

* generator.cpp :
  Needs the input matrix and seed value and thereby gives the intermediate output for control flow in files and final output on STDOUT. 
  
  -Input : raw.txt, seed_matrix.txt
  -Output : final_matrix.txt, test.txt, STDOUT etc.

Methodology:
====================

The program begins by reading in the input file which is an unsolved 9x9 sudoku puzzle and it is minimally encoded and then pushed into miniSAT.  MiniSAT will output if the problem is SATISFIABLE or UNSATISFIABLE.  In the case of the sudoku problem, it is indeed SATISFIABLE. The SAT output gets outputted to the text file "decode.txt". The program will then attempt to decode the puzzle encoding and then finally produce the solution to the problem, by
outputting to the STDOUT.

