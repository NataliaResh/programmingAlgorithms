#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

bool isIdealPermutation(vector<int>& nums) {
  int m = nums[0];
  for (int i = 2; i < nums.size(); i++) {
    if (m > nums[i]) {
      return false;
    }
  m = max(m, nums[i - 2]);
  }
  return true;
}

int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  cout << isIdealPermutation(a);
}
