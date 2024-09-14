#include <vector>
#include <iostream>

using namespace std;

int maxProfit(vector<int>& prices) {
    size_t profit = 0;
    for (size_t i = 1; i < prices.size(); i++) {
        if (prices[i - 1] < prices[i]) {
            profit += prices[i] - prices[i - 1];
        }
    }
    return profit;
}

int main() {
  vector<int> a = {7, 1, 5, 3, 6, 4};
  cout << maxProfit(a) << "\n";
}
