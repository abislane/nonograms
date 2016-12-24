# nonograms

an object oriented solver for nonograms. Uses depth first search with regards to rows to construct the puzzles, and performs validations at each step to prune possible solutions

## input specifications

The input comes in through stdin.
The first line of input is two integers, m and n, denoting the number of rows and columns in the puzzle
The next m lines denote the hints for each row
The next n lines denote the hints for each column

Example inputs can be found in the inputs folder

## building the project
The project builds with c++11 in gcc. A Makefile is included in the repo. Download the files into a new directory and type `make` into the terminal to build the project. An executable names `solver` will be created.

## future features
* Better pruning
* multicolor nonograms
* "smart" solver
