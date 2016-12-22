#include "line.h"
#include "grid.h"
#include <iostream>
#include <sstream>

using namespace std;

int main()
{
  int m, n, i, clue;
  string line;
  stringstream tokens;
  vector<int> line_clues;
  cin >> m >> n;

  Grid puzzle(m, n);

  //flush line
  getline(cin, line);

  for(i = 0; i < m; i++)
  {
    getline(cin, line);
    tokens.clear();
    tokens.str(line);
    line_clues.clear();

    while(tokens >> clue)
    {
      line_clues.push_back(clue);
    }

    if(!(line_clues.size() == 0 && line_clues[0] == 0))
    {
      puzzle.add_row_clues(i, line_clues);
    }
  }

  for(i = 0; i < n; i++)
  {
    getline(cin, line);
    tokens.clear();
    tokens.str(line);
    line_clues.clear();


    while(tokens >> clue)
    {
      line_clues.push_back(clue);
    }

    if(!(line_clues.size() == 1 && line_clues[0] == 0))
    {
      puzzle.add_col_clues(i, line_clues);
    }
  }

  bool solved = puzzle.solve();
  puzzle.print_grid();
}
