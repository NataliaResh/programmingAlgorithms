#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

void swap(vector<int> &array, int i, int j) {
  int temp = array[i];
  array[i] = array[j];
  array[j] = temp;
}

void merge(vector<int> &array, int s1, int e1, int s2, int e2, int sb) {
  while (s1 <= e1 && s2 <= e2) {
    if (array[s1] <= array[s2]) {
      swap(array, sb++, s1++);
    } else {
      swap(array, sb++, s2++);
    }
  }
  while (s1 <= e1) {
    swap(array, sb++, s1++);
  }
  while (s2 <= e2) {
    swap(array, sb++, s2++);
  }
}

void merge_sort(vector<int> &array, int start, int end, int bstart) {
  if (end - start <= 0) {
    return;
  }
  int middle = (end + start) / 2;
  merge_sort(array, start, middle, bstart);
  merge_sort(array, middle + 1, end, bstart);
  merge(array, start, middle, middle + 1, end, bstart);
  while (start <= end) {
    swap(array, start++, bstart++);
  }
}

void sorting_insert(vector<int> &array, int i) {
  for (; i < array.size() - 1 && array[i + 1] < array[i]; i++) {
    swap(array, i, i + 1);
  }
}

void in_place_merge_sort(vector<int> &array, int s, int e) {
  int p = (s + e) / 2 + 1;
  int pp = (p + 1) / 2;
  int p1s = 2 * pp - p;
  merge_sort(array, p, e, 0);
  while (pp - p1s > 0) {
    merge_sort(array, p1s, pp - 1, pp);
    merge(array, p1s, pp - 1, p, e, pp);
    p = pp;
    pp = (p + 1) / 2;
    p1s = 2 * pp - p;
    for (int i = 0; i < array.size(); i++) {
      cout << array[i] << " ";
    }
    cout << "\n";
    cout << "p = " << p << " pp = " << pp << " p1s = " << p1s << "\n";
  }
  sorting_insert(array, 0);
}

int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  in_place_merge_sort(a, 0, n - 1);
  for (int i = 0; i < n; i++) {
    cout << a[i] << " ";
  }
  cout << "\n";
}
