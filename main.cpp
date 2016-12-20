#include "line.h"
#include <iostream>

using namespace std;

int main()
{
  Line test(5);
  test.put(0, 1);
  test.put(2, 1);
  test.put(4, 1);

  int *data = test.get_data();
  for(int i = 0; i < test.get_size(); i++)
  {
    cout << data[i] << " ";
  }
  cout << endl;

  vector<int> clues;
  clues.push_back(1);
  clues.push_back(3);
  for(int i = 1; i <= test.get_size(); i++)
  {
    // expecting 11100 for as sequence of all tests
    cout << test.is_valid(clues, i) << endl;
  }
  cout << "----------------------------" << endl;

  Line test1(5);
  test1.put(0, 1);
  test1.put(2, 1);
  test1.put(3, 1);
  Line test2(5);
  test2.put(0, 1);
  test2.put(3, 1);
  test2.put(4, 1);
  Line test3(5);
  test3.put(1, 1);
  test3.put(3, 1);
  test3.put(4, 1);

  vector<int> clues1;
  clues1.push_back(1);
  clues1.push_back(2);
  // all three tests shouls be valid
  cout << test1.is_valid(clues1, 5) << endl;
  cout << test2.is_valid(clues1, 5) << endl;
  cout << test3.is_valid(clues1, 5) << endl;
  return 0;
}