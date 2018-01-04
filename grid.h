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
  bool solved();
  void print_grid();
private:
  int rows;
  int cols;
  int turn;
  std::vector<std::vector<int>> row_clues;
  std::vector<std::vector<int>> col_clues;
  std::vector<Line> lines;

  bool verify_columns(int upto);
  Line create_column(int col);
  void update_column(int col, Line line);
  void update_row(int row, Line line);
  bool solve_row(int row);
  bool solve_col(int col);
  void next_turn();
};

#endif
