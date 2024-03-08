#include <vector>

using namespace std;
class MinStack {
  vector<int> minimums_;
  vector<int> stack_;

public:
  MinStack() {}

  void push(int val) {
    if (stack_.empty()) {
      minimums_.push_back(val);
    } else {
      minimums_.push_back(min(val, minimums_.back()));
    }
    stack_.push_back(val);
  }

  void pop() {
    stack_.pop_back();
    minimums_.pop_back();
  }

  int top() { return stack_.back(); }

  int getMin() { return minimums_.back(); }
};
