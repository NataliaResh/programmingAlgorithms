#include <vector> 

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

  void shiftUp(int i) {
    
  }
  
  void shiftDown(int i) {
    int ind = i * 2;
    if (ind >= heap_.size()) return;
    ListNode* val = heap_[ind];
    if (ind + 1 < heap_.size() && heap_[ind + 1] > val) {
      
    }
  }
};

ListNode* mergeKLists(vector<ListNode*>& lists) {
        
}

