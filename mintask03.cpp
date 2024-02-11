#include <iostream>
#include <vector>

using namespace std;


int search(vector<int>& nums, int target) {
        int l = 0, r = nums.size() - 1;
        while (l <= r) {
            int m = (l + r) / 2;
            if (nums[m] == target) return m;
            if (nums[m] < target) l = m + 1;
            else r = m - 1;
        }
        return -1;
}

int main() {
  vector<int> nums = {1, 2, 3, 4, 5};
  cout << search(nums, 1);
}
