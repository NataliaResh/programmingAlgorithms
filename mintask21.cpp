#include <cassert>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <ios>
#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>

using namespace std;

class BinomialHeap {
  public:
  vector<BinomialHeap *> *heap_;
  BinomialHeap *up_ = NULL;
  int degree_ = 0;
  int priority_ = 0;
  bool hightLevel_;

  static BinomialHeap *mergeTree(BinomialHeap *t1, BinomialHeap *t2) {
    assert(t1->degree_ == t2->degree_);
    if (t1->priority_ < t2->priority_) {
      t1->heap_->push_back(t2);
      t2->up_ = t1;
      t1->degree_++;
      return t1;
    } else {
      t2->heap_->push_back(t1);
      t1->up_ = t2;
      t2->degree_++;
      return t2;
    }
  }

  void merge(BinomialHeap *bh2) {
    if (!bh2) return;
    vector<BinomialHeap*> *ansHeap = new vector<BinomialHeap*>;
    BinomialHeap *carry = NULL;
    vector<BinomialHeap*> *heap1 = heap_, *heap2 = bh2->heap_;
    int n = heap1->size(), m = heap2->size();
    int i = 0;
    int j = 0;
    for (int d = 0; i < n && j < m; d++) {
      if (heap1->at(i)->degree_ == d && heap2->at(j)->degree_ == d && carry) {
        carry->up_ = NULL;
        ansHeap->push_back(carry);
        carry = mergeTree(heap1->at(i++), heap2->at(j++));
      } else if (heap1->at(i)->degree_ == d && heap2->at(j)->degree_ == d) {
        carry = mergeTree(heap1->at(i++), heap2->at(j++));
      } else if (heap1->at(i)->degree_ && carry) {
        carry = mergeTree(heap1->at(i++), carry);
      } else if (heap2->at(j)->degree_ == d && carry) {
        carry = mergeTree(heap2->at(j++), carry);
      } else if (heap1->at(i)->degree_ == d) {
        ansHeap->push_back(heap1->at(i++));
      } else if (heap2->at(j)->degree_ == d) {
        heap2->at(j)->up_ = NULL;
        ansHeap->push_back(heap2->at(j++));
      } else if (carry) {
        carry->up_ = NULL;
        ansHeap->push_back(carry);
        carry = NULL;
      }
    }
    while (i < n) {
      if (carry && carry->degree_ == heap1->at(i)->degree_) {
        carry = mergeTree(heap1->at(i++), carry);
      } else if (carry) {
        carry->up_ = NULL;
        ansHeap->push_back(carry);
        carry = NULL;
      } else {
        ansHeap->push_back(heap1->at(i++));
      }
    }
    while (j < m) {
      if (carry && carry->degree_ == heap2->at(j)->degree_) {
        carry = mergeTree(heap2->at(j++), carry);
      } else if (carry) {
        carry->up_ = NULL;
        ansHeap->push_back(carry);
        carry = NULL;
      } else {
        heap2->at(j)->up_ = NULL;
        ansHeap->push_back(heap2->at(j++));
      }
    }
    if (carry) {
      ansHeap->push_back(carry);
    }
    heap_ = ansHeap;
  }

  void shiftUp(BinomialHeap *bh) {
    if (!bh->up_) return;
    if (bh->priority_ < bh->up_->priority_) {
      int pivot = bh->priority_;
      bh->priority_ = bh->up_->priority_;
      bh->up_->priority_ = pivot;
      shiftUp(bh->up_);
    }
  }

//public:
  
  BinomialHeap() : hightLevel_(true), heap_(new vector<BinomialHeap*>){}

  BinomialHeap(int priority, bool hightLevel) : hightLevel_(hightLevel), heap_(new vector<BinomialHeap*>) {
    if (hightLevel_) {
      BinomialHeap *pivot = new BinomialHeap(priority, false);
      heap_->push_back(pivot);
    } else {
      priority_ = priority;
    }
  }

  int peekMin() {
    if (!heap_->size()) {
      cout << "Try extract min from empty heap!\n";
      exit(1);
    }
    int ans = heap_->at(0)->priority_;
    for (int i = 1; i < heap_->size(); i++) {
      ans = min(ans, heap_->at(i)->priority_);
    }
    return ans;
  }

  void insert(int priority) {
    BinomialHeap *pivot = new BinomialHeap(priority, true);
    merge(pivot);
  }

  void decreaseKey(BinomialHeap *bh, int priority) {
    if (priority > bh->priority_) return;
    bh->priority_ = priority;
    shiftUp(bh);
  }

  int extractMin() {
    if (!heap_->size()) {
      cout << "Try exxtract min from empty heap!\n";
      exit(1);
    }
    BinomialHeap *ans = heap_->at(0);
    int ind = 0;
    for (int i = 1; i < heap_->size(); i++) {
      if (ans->priority_ > heap_->at(i)->priority_) {
        ans = heap_->at(i);
        ind = i;
      }
    }
    heap_->erase(heap_->begin() + ind);
    merge(ans);
    return ans->priority_;
  }

  void deleteKey(BinomialHeap *bh) {
    decreaseKey(bh, INT32_MIN);
    extractMin();
  }
};

void test() {
  BinomialHeap *heap = new BinomialHeap();
  for (int i = 10; i >= 0; i--) {
    heap->insert(i);
  }
  for (int i = 15; i <= 20; i++) {
    heap->insert(i);
  }
  assert(heap->peekMin() == 0);
    for (int i = 0; i <= 10; i++) {
    assert(heap->extractMin() == i); 
  }
  for (int i = 15; i <= 20; i++) {
    assert(heap->extractMin() == i);
  }
}

int main() {
  test();
  cout << "All tests passed!\n";
  }
