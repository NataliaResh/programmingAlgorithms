#include <cstddef>
#include <vector>

using namespace std;

bool canJump(vector<int>& nums) {
    size_t size = nums.size();
    size_t sizeJump = 0;
    for (size_t i = size - 1; i > 0; i--) {
        if (sizeJump <= nums[i]) {
            sizeJump = 0;
        }
        sizeJump++;
    }
    return sizeJump <= nums[0];
}

int main() {
    
}
