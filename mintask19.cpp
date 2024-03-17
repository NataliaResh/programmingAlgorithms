#include <cinttypes>
#include <ios>
#include <vector> 
#include <iostream>

using namespace std;

struct ListNode {
   int val;
   ListNode *next;
   ListNode() : val(0), next(nullptr) {}
   ListNode(int x) : val(x), next(nullptr) {}
   ListNode(int x, ListNode *next) : val(x), next(next) {}
 };
 
class Heap {
  vector<ListNode*> heap_;
  
  void shiftDown(int i) {
    int ind = (i + 1) * 2 - 1;
    if (ind >= heap_.size()) return;
    if (ind + 1 < heap_.size() && heap_[ind + 1] < heap_[ind]) {
      ind++;
    }
    if (heap_[i]->val <= heap_[ind]->val) return;
    swap(heap_[i], heap_[ind]);
    shiftDown(ind);
  }
  
  void pop_first() {
      swap(heap_[0], heap_[heap_.size() - 1]);
      heap_.pop_back();
      if (heap_.size() > 0) {
        shiftDown(0);
      }
  }
  public:
  Heap (vector<ListNode*>& lists) {
    for (int i = 0; i < lists.size(); i++) {
      if (lists[i]) {
        heap_.push_back(lists[i]);
      }
    }
    int middle = lists.size() / 2;
    for (int i = middle; i >= 0; i--) {
      shiftDown(i);
    }
  }

  ListNode *extract_min() {
    if (!heap_[0]) {
      pop_first();
      return extract_min();
    }
    int ans = heap_[0]->val;
    heap_[0] = heap_[0]->next;
    if (!heap_[0]) {
      pop_first();
    }
    shiftDown(0);
    return new ListNode(ans);
  }

  bool empty() {
    return heap_.empty();
  }
};

ListNode* mergeKLists(vector<ListNode*>& lists) {
    Heap *heap = new Heap(lists);
    if (heap->empty()) {
        return nullptr;
    }
    ListNode *newList = heap->extract_min();
    ListNode *a = newList;
    while (!heap->empty()) {
      ListNode *tmp = heap->extract_min();
      a->next = tmp;
      a = tmp;
    }
    return newList;
}

int main() {
  ListNode *a = new ListNode(4);
  ListNode *b = new ListNode(1, a);
  ListNode *a1 = new ListNode(3);
  ListNode *b1 = new ListNode(1, a1);
  vector<ListNode*> lists = {b, b1};
  ListNode *ans = mergeKLists(lists);
  while (ans) {
    cout << ans->val << " ";
    ans = ans->next;
  }
  cout << "\n";
}
