# nonograms

an object oriented solver for nonograms. Repeatedly goes over each row and column, filling or crossing out squares when logically sound. This is much smarter and quicker than the earlier release, which use a brute force DFS approach.

## input specifications

The input comes in through stdin.
The first line of input is two integers, m and n, denoting the number of rows and columns in the puzzle
The next m lines denote the hints for each row
The next n lines denote the hints for each column

Example inputs can be found in the inputs folder

## building the project
The project builds with c++11 in gcc. A Makefile is included in the repo. Download the files into a new directory and type `make` into the terminal to build the project. An executable named `solver` will be created.
