#ifndef GRID_H
#define GRID_H

#include "line.h"

class Grid
{
public:
  Grid(int m, int n);
  void add_row_clues(int row, std::vector<int> clues);
  void add_col_clues(int col, std::vector<int> clues);
  bool solve();
  void print_grid();
private:
  int rows;
  int cols;
  std::vector<std::vector<int>> row_clues;
  std::vector<std::vector<int>> col_clues;
  std::vector<Line> lines;

  bool verify_columns(int upto);
  Line create_column(int col);
  int solve_row(int row);
};

#endif
