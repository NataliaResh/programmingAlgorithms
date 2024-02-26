#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

void in_place_merge_sort(vector<int> &array, int s, int e);


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
  // cout << "merge sort s = " << start << " e = " << end << " b = " << bstart << "\n";
  // for (int i = 0; i < array.size(); i++) {
  //     cout << array[i] << " ";
  //   }
  //   cout << "\n";
  //   int t;
  //   cin >> t;
  if (end - start == 0) {
    swap(array, start, bstart);
    return;
  }
  int middle = (end + start) / 2;
  //merge_sort(array, start, middle, bstart);
  //merge_sort(array, middle + 1, end, bstart);
  in_place_merge_sort(array, start, middle);
  in_place_merge_sort(array, middle + 1, end);
  merge(array, start, middle, middle + 1, end, bstart);
  // while (start <= end) {
  //   swap(array, start++, bstart++);
  // }
}

void sorting_insert(vector<int> &array, int s, int e) {
  for (; s < e && array[s + 1] < array[s]; s++) {
    swap(array, s, s + 1);
  }
}
// 0 1 2 3 4 5 6 
//  4 5 6 
//  4 - (6 - 4+ 1) = 1
// pp + (pp - p1s)
// p - 1 - p + (e - p + 1) = -1 + e - p + 1 = e - p
// pp + pp - p1s - pp = pp - p1s
//
int ii = 1;
void in_place_merge_sort(vector<int> &array, int s, int e) {
  int jj = ii;
  // cout << "inplace: s= " << s << " e = " << e <<  " i= " << ii++ <<"\n";
  // for (int i = 0; i < array.size(); i++) {
  //     cout << array[i] << " ";
  //   }
  //   cout << "\n";
  //   cout << "s = " << s << " e = " << e << "\n";
  //   int t;
  //   cin >> t;
  if (e - s == 1) {
    if (array[s] > array[e]) {
      swap(array, s, e);
    }
    return;
  }
  if (e - s <= 0) return;
  int p = (s + e) / 2 + 1;
  int pp = (s + p + 1) / 2;
  int p1s = 2 * pp - p;
  //in_place_merge_sort(array, p, e);
  merge_sort(array, p - (e - p + 1), p - 1, p);
  //cout << "sort to second" << "\n";
  // cout.flush();
  while (pp - p1s > 0) {
    // cout << "p = " << p <<  " pp = " << pp << " p1s = " << p1s << "\n";
    merge_sort(array, pp, pp + (pp - p1s) - 1, p1s);
    //merge_sort(array, p1s, pp - 1, pp);
    //in_place_merge_sort(array, p1s, pp - 1);
    merge(array, p1s, pp - 1, p, e, pp);
    p = pp;
    pp = (s + p + 1) / 2;
    p1s = 2 * pp - p;
    
  }
  sorting_insert(array, s, e);
  // for (int i = 0; i < array.size(); i++) {
  //     cout << array[i] << " ";
  //   }
  //   cout << "\n";
  //   cout << "s = " << s << " e = " << e << " p = " << p << " pp = " << pp << " p1s = " << p1s << "\n";
  //   cout << "in place end i=" << jj << "\n"; 
  //   cin >> t;

}

int main() {
  // int n;
  // cin >> n;
  // vector<int> a(n);
  // for (int i = 0; i < n; i++) {
  //   cin >> a[i];
  // }
  // vector<int> a = {4, 9, 4, 1, 0, 7, -1, 2, 4, 2, 10, 3};
  vector<int> a = {-74,48,-20,2,10,-84,-5,-9,11,-24,-91,2,-71,64,63,80,28,-30,-58,-11,-44,-87,-22,54,-74,-10,-55,-28,-46,29,10,50,-72,34,26,25,8,51,13,30,35,-8,50,65,-6,16,-2,21,-78,35,-13,14,23,-3,26,-90,86,25,-56,91,-13,92,-25,37,57,-20,-69,98,95,45,47,29,86,-28,73,-44,-46,65,-84,-96,-24,-12,72,-68,93,57,92,52,-45,-2,85,-63,56,55,12,-85,77,-39};

  int n = a.size();
  in_place_merge_sort(a, 0, n - 1);
  for (int i = 0; i < n; i++) {
    cout << a[i] << " ";
  }
  cout << "\n";
}
