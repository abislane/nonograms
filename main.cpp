#include "line.h"
#include "grid.h"
#include <iostream>
#include <sstream>

using namespace std;

int main()
{
  int m, n, i, clue;
  unsigned int j;
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

    cout << "doing row #" << i << endl;
    cout << tokens.str() << endl;

    while(tokens >> clue)
    {
      cout << "f ";
      line_clues.push_back(clue);
    }
    cout << endl;

    if(!(line_clues.size() == 0 && line_clues[0] == 0))
    {
      puzzle.add_row_clues(i, line_clues);
    }

    for(j = 0; j < line_clues.size(); j++)
    {
      cout << line_clues[j] << " ";
    }
    cout << endl;
  }

  for(i = 0; i < n; i++)
  {
    getline(cin, line);
    tokens.clear();
    tokens.str(line);
    line_clues.clear();

    cout << "doing col #" << i << endl;

    while(tokens >> clue)
    {
      line_clues.push_back(clue);
    }

    if(!(line_clues.size() == 1 && line_clues[0] == 0))
    {
      puzzle.add_col_clues(i, line_clues);
    }

    for(j = 0; j < line_clues.size(); j++)
    {
      cout << line_clues[j] << " ";
    }
    cout << endl;
  }

  bool solved = puzzle.solve();
  puzzle.print_grid();
}
