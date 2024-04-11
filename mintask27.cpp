#include <vector>
#include <map>
#include <iostream>

using namespace std;

class FreqStack {
    map<int, vector<int>> stack_;
    map<int, int> stackMap_;
    int maxFreq_ = 0;

public:
    FreqStack() {}
    
    void push(int val) {
        if (stackMap_.find(val) == stackMap_.end()) {
            stackMap_[val] = 0;
        }
        stackMap_[val]++;
        int freq = stackMap_[val];
        stack_[freq].push_back(val);
        if (freq > maxFreq_) {
          maxFreq_ = freq;
        }
      }
    
    int pop() {
        int ans = stack_[maxFreq_].back();
        stack_[maxFreq_].pop_back();
        stackMap_[ans]--;
        if (stack_[maxFreq_].empty()) {
          maxFreq_--;
        }
        return ans;
    }
};

int main() {
  FreqStack *f = new FreqStack();
  f->push(1);
  f->push(2);
  cout << f->pop() << " " << f->pop() << "\n";
}
