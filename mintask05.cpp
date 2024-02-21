#include <iostream>
#include <vector>

using namespace std;

void inserting_sort_k(vector<int> &array, int k) {
  for (int i = k - 1; i < array.size(); i++) {
    for (int j = i; j - k >= 0 && array[j] > array[j - k]; j-=k) {
      int temp = array[j];
      array[j] = array[j - k];
      array[j - k] = temp;
    }
  }
}

int hIndex(vector<int> &citations) {
  const int shell_numbers[] = {701, 301, 132, 57, 23, 10, 4, 1};
  for (auto k : shell_numbers) {
    inserting_sort_k(citations, k);
  }
  int left = 0, right = citations.size() - 1;
  int ans = 0;
  while (left <= right) {
    int pivot = (left + right) / 2;
    if (citations[pivot] >= pivot + 1) {
      left = pivot + 1;
      ans = left;
    } else {
      right = pivot - 1;
    }
  }
  return ans;
}

int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  cout << hIndex(a) << "\n";
  for (int i = 0; i < n; i++) {
    cout << a[i] << " ";
  }
  cout << "\n";
}
