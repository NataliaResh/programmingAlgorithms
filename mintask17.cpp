struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};
 

ListNode* reverseBetween(ListNode* head, int left, int right) {
  ListNode *zeroNode = new ListNode(0, head);
  ListNode *beforeLeft = zeroNode, *current = head;
  for (int i = 0; i < left - 1; i++) {
    ListNode *tmp = current->next;
    beforeLeft = current;
    current = tmp;
  }
  ListNode *prev = nullptr;
  for (int i = 0; i < right - left + 1; i++) {
    ListNode *tmp = current->next;
    current->next = prev;
    prev = current;
    current = tmp;
  }
  beforeLeft->next->next = current;
  beforeLeft->next = prev;
  return zeroNode->next;
}
