#include "line.h"
#include <stdexcept>

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
  int i;
  for(i = 0; i < size; i++)
  {
    filled[i] = 0;
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

