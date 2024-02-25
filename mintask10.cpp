#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int COUNT_CHAR = 256;

vector<string> countingSort(const vector<string> &array, int index) {
  vector<int> counts(COUNT_CHAR, 0);
  vector<string> ans(array.size());
  for (int i = 0; i < array.size(); i++) {
    counts[array[i][index]]++;
  }
  for (int i = 1; i < COUNT_CHAR; i++) {
    counts[i] += counts[i - 1];
  }
  for (int i = array.size() - 1; i >= 0; i--) {
    char j = array[i][index];
    int cur_i = counts[j] - 1;
    ans[cur_i] = array[i];
    counts[j]--;
  }
  return ans;
}

vector<string> radixSort(vector<string> array) {
  if (array.size() <= 0) {
    return array;
  }
  for (int i = array[0].size() - 1; i >= 0; i--) {
    array = countingSort(array, i);
  }
  return array;
}

void test(vector<string> array1) {
  vector<string> array2(array1);
  sort(array1.begin(), array1.end());
  assert(array1 == radixSort(array2));
  
}
int main() {
  test({"abc", "cbd", "ava"});
  test({"qwerty", "aaaaaa", "bacaba", "123456", "bababa", "babaca"});
  test({"bbb", "bba", "cba", "cab", "ccc", "cca", "ccb", "acb", "aba", "aaa"});
  test({"bac", "cab", "Cab", "Bac", "AAa", "aaa"});
  test({"12", "20", "09", "71", "00", "10", "23"});
  test({"", ""});
  test({"b", "r", "q", "a", "l", "o", "g", "c", "m", "z", "s", "w", "e", "i", "p", "t", "n", "x", "n", "u", "d", "f", "h", "j", "k"});
  test({"10101", "11001", "10000", "222222", "21211", "12121"});
  test({});
  test({"cccccccccc", "ccccccccccb", "ccccccccca", "bbbbbbbbbb", "baaaaaaaaa"});

  cout << "All tests passed!\n";
}
