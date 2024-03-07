struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if (!head) return nullptr;
        ListNode *slow = head, *fast = head;
        while (fast->next && fast->next->next) {
          slow = slow->next;
          fast = fast->next->next;
          if (slow == fast) {
            while (slow != head) {
              slow = slow->next;
              head = head->next;
            }
            return head;
          }
        }
          return nullptr;
    }
};
