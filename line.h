#ifndef LINE_H
#define LINE_H

#include <vector>
#include <string>

class Line
{
public:
  Line(int s);
  ~Line();
  Line & operator=(const Line & other); 
  void put(int index, int type);
  void clear();
  int *get_data();
  int get_size();
  bool is_valid(std::vector<int> clues, int upto);
  void fill_line(std::vector<int> clues, std::vector<int> perm);
private:
  std::vector<int> get_blocks_upto(int upto);
  int size;
  int *filled;
};

int num_slots(std::vector<int> clues, int size);
std::vector<int> combo_str_to_vector(std::string bitmask);

#endif
