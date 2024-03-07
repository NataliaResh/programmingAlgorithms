#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <cassert>

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
  
  int size() const {return size_; }
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

void test(int n) {
  Vector *v = new Vector(4);
  for (int i = 0; i < n; i++) {
    v->push_back(i);
  }
  assert(v->size() == n);
  assert(v->at(n - 1) == n - 1);
  for (int i = 0; i < n / 2; i++) {
    v->pop_back();
  }
  assert(v->size() == n - n / 2);
  assert(v->at(n - n / 2 - 1) == n - n / 2 - 1);
  delete v;
}

int main() {
  test(10);
  test(16);
  test(17);
  test(35);
  test(60);
  cout << "All tests passed\n";
}
