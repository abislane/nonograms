#include "grid.h"
#include <algorithm>
#include <string>
#include <iostream>

#define COLOR_YELLOW "\x1b[33m"
#define COLOR_WHITE  "\x1b[37m"
#define COLOR_RESET  "\x1b[0m"

Grid::Grid(int m, int n)
{
  int i;
  rows = m;
  cols = n;
  turn = 0;

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


void Grid::print_horizontal_gridlines() {
  int k;
  std::cout << COLOR_WHITE;
  for(k = 0; k < cols; k++) {
    if(k % 5 == 0) {
      std::cout << "+";
    }
    std::cout << "-";
  }
  std::cout << "+" << std::endl;
}
void Grid::print_grid()
{
  int i, j;
  int *data, *turns;

  for(i = 0; i < rows; i++)
  {
    // print horizontal border between 5x5 subgrids
    if(i % 5 == 0)
    {
      print_horizontal_gridlines();
    }

    data = lines[i].get_data();
    turns = lines[i].get_turns();
    for(j = 0; j < cols; j++)
    {
      // print vertical border between 5x5 subgrids
      if(j % 5 == 0) {
        std::cout << COLOR_WHITE << "|";
      }

      if(turns[j] == turn)
      {
        std::cout << COLOR_YELLOW;
      }
      else
      {
        std::cout << COLOR_WHITE;
      }

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
    std:: cout << "|" << std::endl;
  }
  print_horizontal_gridlines();
  std::cout << COLOR_RESET;
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
    next_turn();
    for(i = 0; i < rows; i++)
    {
      solve_row(i);
    }

    print_grid();
    std::cout << std::endl;
    
    next_turn();
    for(i = 0; i < cols; i++)
    {
      solve_col(i);
    }

    print_grid();
    std::cout << std::endl;
  }

  // increment the turns one more time to make the final result all white
  next_turn();
  return true;
}

void Grid::next_turn() {
  int i;
  for(i = 0; i < rows; i++) {
    lines[i].next_turn();
  }
  turn++;
}

bool Grid::solve_row(int r)
{
  Line new_line(cols, turn);
  bool new_line_assigned;
  std::vector<int> combo;

  int k = row_clues[r].size();
  int n = num_slots(row_clues[r], cols);
  
  std::string bitmask(k, '1');
  bitmask.resize(n, '0');

  Line old_line = lines[r];
  new_line_assigned = false;
  Line candidate = Line(cols, turn);

  if(old_line.solved()) 
  {
    return false;
  }

  do
  {
    combo = combo_str_to_vector(bitmask);
    candidate.fill_line(row_clues[r], combo);

    if(candidate.matches(old_line)) 
    {
      if(!new_line_assigned) 
      {
        new_line = candidate;
        new_line_assigned = true;
      }
      else
      {
        new_line.intersect_lines(candidate);
      }
    }

    if(new_line_assigned && new_line.equals(old_line)) {
      return false; // no changes will be able to be made
    }
    
  } while(std::prev_permutation(bitmask.begin(), bitmask.end()));

  if(new_line_assigned)
  {
    update_row(r, new_line);
  }
  return false;
}

bool Grid::solve_col(int c)
{
  Line new_line(rows, turn);
  bool new_line_assigned;
  std::vector<int> combo;

  int k = col_clues[c].size();
  int n = num_slots(col_clues[c], rows);
  
  std::string bitmask(k, '1');
  bitmask.resize(n, '0');

  Line old_line = create_column(c);
  new_line_assigned = false;
  Line candidate = Line(rows, turn);

  if(old_line.solved()) 
  {
    return false;
  }

  do
  {
    combo = combo_str_to_vector(bitmask);
    candidate.fill_line(col_clues[c], combo);

    if(candidate.matches(old_line)) 
    {
      if(!new_line_assigned) 
      {
        new_line = candidate;
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
    update_column(c, new_line);
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

void Grid::update_column(int col, Line line)
{
  int i;
  int *new_data = line.get_data();
  for(i = 0; i < rows; i++) 
  {
    if(lines[i].get_data()[col] != new_data[i])
    {
      lines[i].put(col, new_data[i]);
    }
  }
}

void Grid::update_row(int row, Line line)
{
  int i;
  int *prev_data = lines[row].get_data(), *new_data = line.get_data();
  for(i = 0; i < cols; i++) 
  {
    if(prev_data[i] != new_data[i])
    {
      lines[row].put(i, new_data[i]);
    }
  }
}
