#include "line.h"
#include <iostream>

using namespace std;

int main()
{
  vector<int> clues;
  clues.push_back(1);
  clues.push_back(2);
  cout << num_slots(clues, 5) << endl;

  std::vector<int> perm;
  perm.push_back(1);
  perm.push_back(2);

  Line test = fill_line(5, clues, perm);
  int* data = test.get_data();

  for(int i = 0; i < 5; i++){
    cout << data[i] << " ";
  }
  cout << endl;
  return 0;
}
