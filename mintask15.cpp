#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include<iostream>

using namespace std;

class Vector {
  int size_ = 0;
  int capacity_;
  int* data_;
  
  int *copyData(int newCapacity) {
    int *newData = new int[newCapacity];
    int len = min(size_, newCapacity);
    for (int i = 0; i < len; i ++) {
      newData[i] = data_[i];
    }
    delete[] data_;
    return newData;
  }
public:
  Vector() : Vector(16) {}
  Vector(int capacity) : capacity_(capacity), data_(new int[capacity_]) {}

  void push_back(int elem) {
    if (size_ == capacity_) {
      capacity_ *= 2;
      data_ = copyData(capacity_);
    }
    data_[size_] = elem;
    size_++;
  }
  
  void pop_back() {
    if (size_ == 0) {
      return;
    }
    if (size_ * 4 <= capacity_) {
      data_ = copyData(size_ * 2);
    }
    size_--;
  }

  int &at(int index) {
    if (index >= size_ || index < 0) {
      exit(1);
    }
    return data_[index];
  }

  ~Vector() {
    delete[] data_;
  }
};

int main() {
  int n;
  cin >> n;
  Vector *a = new Vector();
  for (int i = 0; i < n; i++) {
    int t;
    cin >> t;
    a->push_back(t);

  }
  for (int i = 0; i < n; i++) {
    cout << a->at(i) << " ";
  }
  cout << "\n";
  delete a;
}
