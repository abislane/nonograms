#include "line.h"
#include "grid.h"
#include <iostream>

using namespace std;

int main()
{
  Grid puzzle(5, 5);
  vector<int> row0, row2, row3, row4, col0, col1, col2, col3, col4;
  row0.push_back(1);
  row2.push_back(1);
  row3.push_back(1);
  row3.push_back(2);
  row4.push_back(4);
  col0.push_back(1);
  col1.push_back(1);
  col1.push_back(3);
  col2.push_back(1);
  col3.push_back(2);
  col4.push_back(1);

  puzzle.add_row_clues(0, row0);
  puzzle.add_row_clues(2, row2);
  puzzle.add_row_clues(3, row3);
  puzzle.add_row_clues(4, row4);

  puzzle.add_col_clues(0, col0);
  puzzle.add_col_clues(1, col1);
  puzzle.add_col_clues(2, col2);
  puzzle.add_col_clues(3, col3);
  puzzle.add_col_clues(4, col4);

  bool valid = puzzle.solve();
  cout << valid << endl;

  puzzle.print_grid();
  return 0;
}
