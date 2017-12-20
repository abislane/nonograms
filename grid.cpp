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
      else if(data[j] == 1)
      {
        std::cout << '*';
      }
      else
      {
        std:: cout << 'X';
      }
    }
    std:: cout << std::endl;
  }
}

bool Grid::solved() 
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
        return false;
      }
    }
  }

  return true;
}

bool Grid::solve()
{
  int i;
  while(!solved())
  {
    for(i = 0; i < rows; i++)
    {
      solve_row(i);
    }

    print_grid();
    std::cout << std::endl;

    for(i = 0; i < cols; i++)
    {
      solve_col(i);
    }

    print_grid();
    std::cout << std::endl;
  }
  return true;
}

bool Grid::solve_row(int r)
{
  Line new_line(cols);
  bool new_line_assigned;
  std::vector<int> combo;

  int k = row_clues[r].size();
  int n = num_slots(row_clues[r], cols);
  
  std::string bitmask(k, '1');
  bitmask.resize(n, '0');

  Line old_line = lines[r];
  new_line_assigned = false;
  Line candidate = Line(cols);

  do
  {
    combo = combo_str_to_vector(bitmask);
    candidate.fill_line(row_clues[r], combo);

    if(candidate.matches(old_line)) 
    {
      if(!new_line_assigned) 
      {
        new_line = Line(candidate);
        new_line_assigned = true;
      }
      else
      {
        new_line.intersect_lines(candidate);
      }
    }
    
  } while(std::prev_permutation(bitmask.begin(), bitmask.end()));

  if(new_line_assigned)
  {
    lines[r] = new_line;
  }
  return false;
}

bool Grid::solve_col(int c)
{
  Line new_line(rows);
  bool new_line_assigned;
  std::vector<int> combo;

  int k = col_clues[c].size();
  int n = num_slots(col_clues[c], rows);
  
  std::string bitmask(k, '1');
  bitmask.resize(n, '0');

  Line old_line = create_column(c);
  new_line_assigned = false;
  Line candidate = Line(rows);

  do
  {
    combo = combo_str_to_vector(bitmask);
    candidate.fill_line(col_clues[c], combo);

    if(candidate.matches(old_line)) 
    {
      if(!new_line_assigned) 
      {
        new_line = Line(candidate);
        new_line_assigned = true;
      }
      else
      {
        new_line.intersect_lines(candidate);
      }
    }
    
  } while(std::prev_permutation(bitmask.begin(), bitmask.end()));

  if(new_line_assigned)
  {
    assign_column(c, new_line);
  }
  return false;
}

bool Grid::verify_columns(int upto)
{
  int i;
  Line column(rows);

  for(i = 0; i < cols; i++)
  {
    column = create_column(i);
    if(!column.is_valid(col_clues[i], upto))
    {
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

void Grid::assign_column(int col, Line line)
{
  int i;
  for(i = 0; i < rows; i++) 
  {
    lines[i].put(col, line.get_data()[i]);
  }
}
