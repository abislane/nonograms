#include "line.h"
#include <stdexcept>
#include <cstring>

Line::Line(int s)
{
  size = s;
  filled = new int[s];
}

Line::~Line()
{
  delete[] filled;
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
  std::memset(filled, 0, size);
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
  return result;
}

bool Line::is_valid(std::vector<int> clues, int upto)
{
  std::vector<int> current_blocks = get_blocks_upto(upto);
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

