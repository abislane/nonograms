#ifndef LINE_H
#define LINE_H

#include <vector>
#include <string>

class Line
{
public:
  Line(int s);
  Line(int s, int t);
  Line(const Line & other);
  Line& operator=(const Line & other);
  ~Line();
  void put(int index, int type);
  void clear();
  int *get_data();
  int *get_turns();
  int get_size();
  bool is_valid(std::vector<int> clues, int upto);
  void fill_line(std::vector<int> clues, std::vector<int> perm);
  void intersect_lines(Line other);
  bool matches(Line other);
  bool solved();
  bool equals(Line other);
  void next_turn();
private:
  std::vector<int> get_blocks_upto(int upto);
  int size;
  int turn;
  int *filled;
  int *turn_updated;
  void fill_x();
};

int num_slots(std::vector<int> clues, int size);
std::vector<int> combo_str_to_vector(std::string bitmask);

#endif
