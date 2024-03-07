#include <algorithm>
#include<iostream>
#include<vector>
#include <cassert>

using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

ii partition(vii &array, int start, int end, int pivot) {
  int i = start, j = end, c = start;
    while (c <= j) {
      if (array[c].second < pivot) {
        swap(array[i++], array[c++]);
      } else if (array[c].second == pivot) {
        c++;
      } else {
        swap(array[c], array[j--]);
      }
    }
    return {i, j};
}

int kth(vii &array, int start, int end, int k) {
  if (end - start <= 0) {
    return array[start].second;
  }
  srand((unsigned) time(NULL));
  int ind = start + (rand() % (end - start + 1));
  int pivot = array[ind].second;
  ii p = partition(array, start, end, pivot);
  int i = p.first, j = p.second;
  if (i <= k && k <= j) {
    return array[k].second;
  }
  if (k < i) {
    return kth(array, start, i - 1, k);
  }
  return kth(array, j + 1, end, k - j - 1);
}

int solution(vii &array) {
  int end = array.size() - 1;
  int k = end / 2;
  return kth(array, 0, end, k);
}

bool in(int x, vi &array) {
  for (auto i: array){
    if (x == i) return true;
  }
  return false;
}

void test(vii array, vi expects) {
  assert(in(solution(array), expects));
}

int main() {
  test({{0, 0}, {1, -3}, {0, -4}, {0, 3}}, {0, -3});
  test({{0, 2}, {1, -3}, {0, -1}, {0, 1}}, {-1, 1});
  test({{0, 0}, {1, -3}, {0, -4}, {0, 3}, {9, 8}}, {0});
  test({{0, 0}, {1, -3}, {0, -4}, {0, 3}, {0, 7}, {1, 1}, {2, 1}}, {0, 1});
  test({{0, 0}, {1, 1}, {0, 1}, {-1, 1}, {0, 2}, {9, 3}, {5, 4}},  {1});
  cout << "All tests passed!\n";
}
