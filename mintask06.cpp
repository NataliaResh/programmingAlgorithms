#include <algorithm>
#include <iostream>
#include <pthread.h>
#include <vector>

using namespace std;

void merge(vector<int> &array, int m, int p, int n, vector<int> &buffer) {
  int i = m, j = p + 1, k = m;
  while (k <= n && i <= p && j <= n) {
    if (array[i] <= array[j]) {
      buffer[k++] = array[i++];
    } else {
      buffer[k++] = array[j++];
    }
  }
  while (i <= p) {
    buffer[k++] = array[i++];
  }
  while (j <= n) {
    buffer[k++] = array[j++];
  }
  for (int i = m; i <= n; i++) {
    array[i] = buffer[i];
  }
}

void merge_sort_imp(vector<int> &array, int start, int end,
                    vector<int> &buffer) {
  if (end - start <= 0) {
    return;
  }
  int middle = (end + start) / 2;
  merge_sort_imp(array, start, middle, buffer);
  merge_sort_imp(array, middle + 1, end, buffer);
  merge(array, start, middle, end, buffer);
}

void merge_sort(vector<int> &array) {
  vector<int> buffer(array.size());
  merge_sort_imp(array, 0, array.size() - 1, buffer);
}
void inserting_sort_k(vector<int> &array, int start, int k) {
  for (int i = start; i < array.size(); i += k) {
    for (int j = i; j - k >= 0 && array[j] > array[j - k]; j -= k) {
      int temp = array[j];
      array[j] = array[j - k];
      array[j - k] = temp;
    }
  }
}

void wiggle_merge(vector<int> &array, vector<int> &buffer) {
  int k = array.size() - 1;
  int i = 0, j = k / 2 + 1;
  while (k >= 0) {
    if (k & 1) {
      buffer[k--] = array[j++];
    } else {
      buffer[k--] = array[i++];
    }
    
  }
  for (int i = 0; i < array.size(); i++) {
    array[i] = buffer[i];
  }
}

void wiggleSort(vector<int> &nums) {
  merge_sort(nums);
  vector<int> buffer(nums.size());
  wiggle_merge(nums, buffer);
}
// void wiggleSort(vector<int>& nums) {
//     vector<int> sorted(nums);
//     sort(sorted.begin(), sorted.end());
//     for (int i=nums.size()-1, j=0, k=i/2+1; i>=0; i--)
//         nums[i] = sorted[i&1 ? k++ : j++];
// }
int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  wiggleSort(a);
  for (int i = 0; i < n; i++) {
    cout << a[i] << " ";
  }
  cout << "\n";
}
