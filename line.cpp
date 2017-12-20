#include "line.h"
#include <algorithm>
#include <stdexcept>
#include <numeric>
#include <iostream>

Line::Line(int s)
{
  size = s;
  filled = new int[s];
  clear();
}

Line::Line(const Line & other)
{
  size = other.size;
  int* data = other.filled;
  int i;
  filled = new int[size];

  for(i = 0; i < size; i++)
  {
    filled[i] = data[i];
  }
}

Line::~Line()
{
  delete[] filled;
}

Line & Line::operator=(const Line & other)
{
  size = other.size;
  delete[] filled;

  filled = new int[size];
  std::copy(other.filled, other.filled + size, filled);
  return *this;
}

void Line::put(int index, int type)
{
  if(index < 0 || index >= size)
  {
    throw std::domain_error("index out of bounds on line");
  }
  filled[index] = type;
}

void Line::clear()
{
  int i;
  for(i = 0; i < size; i++)
  {
    filled[i] = 0;
  }
}

void Line::fill_x() {
  int i;
  for(i = 0; i < size; i++)
  {
    filled[i] = -1;
  }
}

int *Line::get_data()
{
  return filled;
}

int Line::get_size()
{
  return size;
}

std::vector<int> Line::get_blocks_upto(int upto)
{
  std::vector<int> result;
  int i;
  int current_block_size = 0;
  for(i = 0; i < upto; i++)
  {
    if (filled[i] == 1)
    {
      current_block_size++;
    }
    else if (i > 0 && filled[i - 1] == 1 && filled[i] == 0)
    {
      result.push_back(current_block_size);
      current_block_size = 0;
    }
  }
  if(current_block_size != 0)
  {
    result.push_back(current_block_size);
  }
  return result;
}

bool Line::is_valid(std::vector<int> clues, int upto)
{
  std::vector<int> current_blocks = get_blocks_upto(upto);
  if(current_blocks.size() == 0 && upto != size)
  {
    return true;
  }

  // check if we know the last block is done being filled
  // this is marked by a 0 at the end, or if we check the entire row
  bool last_block_done = (upto == size || filled[upto - 1] == 0);
  unsigned int i;

  // if we have more blocks than clues, then something is wrong
  if(current_blocks.size() > clues.size())
  {
    return false;
  }

  for(i = 0; i < current_blocks.size() - 1; i++)
  {
    // verify that the completed blocks are the right size
    if (current_blocks[i] != clues[i])
    {
      return false;
    }
  }


  if (last_block_done)
  {
    // make sure that we cover all clues if we are checking the whole row
    if(upto == size && current_blocks.size() < clues.size())
    {
      return false;
    }
    // the last block is done, so we check the whole thing
    return current_blocks[current_blocks.size() - 1] == clues[current_blocks.size() - 1];
  }
  else
  {
    //the last block is not done, so verify that it isn't larger than it should be
    return current_blocks[current_blocks.size() - 1] <= clues[current_blocks.size() - 1];
  }
}

/*
 * given clues and the size of a line, find how many "spaces" there are for collections of blocks
 */
int num_slots(std::vector<int> clues, int size)
{
  if(clues.size() == 0)
  {
    return size;
  }
  return size - std::accumulate(clues.begin(), clues.end(), 0) + 1;
}

/*
 * Given a bitmask representing a permutation, construct a vector of the indecies where we have a 1
 */
std::vector<int> combo_str_to_vector(std::string bitmask)
{
  std::vector<int> result;
  unsigned int j;
  for(j = 0; j < bitmask.length(); j++)
  {
    if(bitmask[j] == '1')
    {
      result.push_back(j);
    }
  }

  // return the amount of arr used by the permutation
  return result;
}

void Line::fill_line(std::vector<int> clues, std::vector<int> perm)
{
  if(clues.size() != perm.size())
  {
    throw new std::domain_error("clues and permuation are of different sizes");
  }

  unsigned int i;
  int j, k;

  clear();
  fill_x();
  for(i = 0; i < clues.size(); i++)
  {
    if(i == 0)
    {
      j = perm[i];
    }
    else
    {
      j = j + perm[i] - perm[i - 1];
    }

    for(k = 0; k < clues[i]; k++, j++)
    {
      put(j, 1);
    }
  }
}

/*
 * returns the closest match between the two given lines. If there is
 * a difference between the lines, a 0 for undetermined is placed. Otherwise,
 * the same data between the lines is added
 */
void Line::intersect_lines(Line other) 
{
  if(size != other.get_size()) 
  {
    throw new std::domain_error("Lines are different sizes");
  }

  int i;
  int* data = other.get_data();

  for(i = 0; i < size; i++) 
  {
    if(filled[i] == data[i]) 
    {
      put(i, filled[i]);
    }
    else 
    {
      put(i, 0);
    }
  }
}

/*
 * checks if this line could be a match with another line. Returns true if all
 * non-zero elements of the other line match up with this line
 */
bool Line::matches(Line other) 
{
  if(size != other.get_size()) 
  {
    throw new std::domain_error("Liens are different sizes");
  }

  int i;
  int* data = other.get_data();

  for(i = 0; i < size; i++)
  {
    if(data[i] != 0 && data[i] != filled[i]) 
    {
      return false;
    }
  }

  return true;
}
