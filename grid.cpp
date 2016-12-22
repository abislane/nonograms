#include "grid.h"
#include <algorithm>
#include <string>
#include <iostream>

Grid::Grid(int m, int n)
{
  int i;
  rows = m;
  cols = n;

  for(i = 0; i < m; i++)
  {
    row_clues.push_back(std::vector<int>());
    lines.push_back(Line(n));
  }

  for(i = 0; i < n; i++)
  {
    col_clues.push_back(std::vector<int>());
  }
}

void Grid::add_row_clues(int row, std::vector<int> clues)
{
  row_clues[row] = clues;
}

void Grid::add_col_clues(int col, std::vector<int> clues)
{
  col_clues[col] = clues;
}

void Grid::print_grid()
{
  int i, j;
  int* data;

  for(i = 0; i < rows; i++)
  {
    data = lines[i].get_data();
    for(j = 0; j < cols; j++)
    {
      if(data[j] == 0)
      {
        std::cout << '.';
      }
      else
      {
        std::cout << '*';
      }
    }
    std:: cout << std::endl;
  }
}

bool Grid::solve()
{
  return solve_row(0);
}

bool Grid::solve_row(int r)
{
  if(r == rows)
  {
    return true;
  }
  
  bool valid;
  std::vector<int> combo;

  int k = row_clues[r].size();
  int n = num_slots(row_clues[r], cols);
  
  std::string bitmask(k, '1');
  bitmask.resize(n, '0');

  do
  {
    combo = combo_str_to_vector(bitmask);
    lines[r].fill_line(row_clues[r], combo);

    if(!verify_columns(r+1))
    {
      print_grid();
      continue;
    }

    std::cout << "OK on row " << r << std::endl;
    print_grid();
    valid = solve_row(r+1);
    if(valid)
    {
      return true;
    }
  } while(std::prev_permutation(bitmask.begin(), bitmask.end()));

  lines[r].clear();
  return false;
}

bool Grid::verify_columns(int upto)
{
  int i, j;
  Line column(rows);

  for(i = 0; i < cols; i++)
  {
    std::cout << "column " << i << ": ";
    column = create_column(i);
    for(j = 0; j < rows; j++)
    {
      std::cout << column.get_data()[j];
    }
    if(!column.is_valid(col_clues[i], upto))
    {
      std::cout << "BAD on column " << i << std::endl;
      return false;
    }
  }
  return true;
}

Line Grid::create_column(int col)
{
  Line result(rows);
  int i;
  for(i = 0; i < rows; i++)
  {
    result.put(i, lines[i].get_data()[col]);
  }

  return result;
}
