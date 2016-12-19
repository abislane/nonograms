#include "line.h"
#include <iostream>

using namespace std;

int main()
{
  Line test(5);
  test.put(1, 3);
  test.put(2, 1);

  int *data = test.get_data();
  for(int i = 0; i < test.get_size(); i++)
  {
    cout << data[i] << " ";
  }
  cout << endl;
  return 0;
}