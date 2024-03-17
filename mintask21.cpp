#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

class BinomialHeap {
  BinomialHeap *down_ = NULL;
  BinomialHeap *right_ = NULL;
  BinomialHeap *up_ = NULL;
  int degree_ = NULL;
  BinomialHeap *last_ = NULL;
  int priority_ = 0;

  static BinomialHeap *unionTrees(BinomialHeap *t1, BinomialHeap *t2) {
    assert(t1->degree_ == t2->degree_);
    if (t1->priority_ < t2->priority_) {
      if (t1->degree_ == 0) {
        t1->down_ = t2;
      } else {
        t1->down_->last_->right_ = t2;
        t1->down_->last_ = t2;
      }
      t2->last_ = t2;
      t2->up_ = t1;
      t1->degree_++;
      return t1;
    } else {
      if (t1->degree_ == 0) {
        t2->down_ = t1;
      } else {
        t2->down_->last_->right_ = t1;
        t2->down_->last_ = t1;
      }
      t1->last_ = t1;
      t1->up_ = t2;
      t2->degree_++;
      return t2;
    }
  }

  static BinomialHeap *merge(BinomialHeap *bh1, BinomialHeap *bh2) {
    if (!bh1 && !bh2) return NULL;
    if (!bh1) return bh2;
    if (!bh2) return bh1;
    BinomialHeap *ans;
    if (bh1->degree_ < bh2->degree_) {
      ans = bh1;
      bh1 = bh1->right_;
    } else {
      ans = bh2;
      bh2 = bh2->right_;
    }
    ans->last_ = ans;
    BinomialHeap *r = ans;
    BinomialHeap *carry = NULL;
    int i = 0;
    while (bh1 || bh2) {
      if (bh1->degree_ == i && bh2->degree_ == i && carry && carry->degree_ == i) {
        r->right_ = carry;
        r->last
      }
    }
  }

public:
  BinomialHeap(int priority, BinomialHeap *down, BinomialHeap *right,
               BinomialHeap *up)
      : priority_(priority), down_(down), right_(right), up_(up) {}

  int peek_min() {
    int ans = priority_;
    BinomialHeap *start = this->right_;
    while (start) {
      ans = min(ans, start->priority_);
    }
    return ans;
  }
};
