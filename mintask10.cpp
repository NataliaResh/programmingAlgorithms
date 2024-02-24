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
  for (int i = array.size() - 1; i >= 0; i--) {
    array = countingSort(array, i);
    cout << "dg\n";
    cout.flush();
  }
  return array;
}

int main() {
  vector<string> a = {"abc", "cbd", "ava"};
  vector<string> b = radixSort(a);
  for (int i = 0; i < a.size(); i++) {
    cout << b[i] << " ";
  }
  cout << "\n";
}
