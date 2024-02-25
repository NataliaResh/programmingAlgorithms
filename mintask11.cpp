#include <vector>
#include <iostream>

using namespace std;

void swap(vector<int> &array, int i, int j) {
  int temp = array[i];
  array[i] = array[j];
  array[j] = temp;
}

void sort(vector<int> &nums) {
  int l = 0, r = nums.size() - 1, i = 0;
  while (i <= r) {
    if (nums[i] == 0) {
      swap(nums, l++, i++);
    } else if (nums[i] == 1) {
      i++;
    } else {
      swap(nums, i, r--);
    }
  }
}

int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  sort(a);
  for (int i = 0; i < n; i++) {
    cout << a[i] << " ";
  }
  cout << "\n";
}
