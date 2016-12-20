#include "line.h"
#include <iostream>

using namespace std;

int main()
{
  vector<int> clues;
  clues.push_back(1);
  clues.push_back(2);
  cout << num_slots(clues, 5) << endl;

  std::vector<int> clues2;
  clues2.push_back(15);
  cout << num_slots(clues2, 15) << endl;

  cout << "--------------------------" << endl;

  unsigned int perm[5];
  int size = combo_str_to_arr(perm, "10011");
  for(int i = 0; i < size; i++){
    std::cout << perm[i] << " ";
  }
  std::cout << std::endl;
  return 0;
}
