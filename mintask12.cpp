#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

pair<int, int> partitionLomuto(vector<int> &array, int start, int end) {
    srand((unsigned) time(NULL));
    int ind = start + (rand() % (end - start + 1));
    int pivot = array[ind];
    swap(array[start], array[ind]);
    int l = start, h = start;
    for (int c = start + 1; c <= end; c++) {
      if (array[c] < pivot) {
        int tmp = array[c];
        array[c] = array[h + 1];
        array[h + 1] = array[l];
        array[l] = tmp;
        l++; h++;
      } else if (array[c] == pivot) {
        swap(array[h + 1], array[c]);
        h++;
      }
    }
    return {l, h};
}

pair<int, int> partitionHoar(vector<int> &array, int start, int end) {
    srand((unsigned) time(NULL));
    int ind = start + (rand() % (end - start + 1));
    int pivot = array[ind];
    int i = start, j = end, c = start;
    while (c <= j) {
      if (array[c] < pivot) {
        swap(array[i++], array[c++]);
      } else if (array[c] == pivot) {
        c++;
      } else {
        swap(array[c], array[j--]);
      }
    }

    return {i, j};
}

void quickSort(vector<int> &array, int start, int end) {
  if (end - start <= 0) return;
  pair<int, int> pivots = partitionLomuto(array, start, end);
  quickSort(array, start, pivots.first - 1);
  quickSort(array, pivots.second + 1, end);
}

int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  quickSort(a, 0, n - 1);
  for (int i = 0; i < n; i++) {
    cout << a[i] << " ";
  }
  cout << "\n";
}
