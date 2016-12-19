#ifndef LINE_H
#define LINE_H

#include <vector>

class Line
{
public:
  Line(int s);
  ~Line();
  void put(int index, int type);
  void clear();
  int *get_data();
  int get_size();
  bool is_valid(std::vector<int> clues, int upto);
private:
  std::vector<int> get_blocks_upto(int upto);
  int size;
  int *filled;
};

#endif