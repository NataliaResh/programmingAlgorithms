#include <cstdlib>
#include <iostream>
#include <random>
#include <set>
#include <vector>
#include <cassert>

using namespace std;

class ImplicitTreap {
    set<int> usingPriorities;

    struct Node {
        int value;
        int priority;
        int count = 1;
        int sum;

        Node *left = nullptr, *right = nullptr;

        Node(int value, set<int>& usingPriorities) : value(value), priority(rand()), sum(value) {
            while (usingPriorities.count(priority) != 0) {
                priority = rand();
            }
            usingPriorities.insert(priority);
        }

        void update() {
            count = 1;
            sum = value;
            if (right) {
                count += right->count;
                sum += right->sum;
            }
            if (left) {
                count += left->count;
                sum += left->sum;
            }
        }
    };

    Node *root_ = nullptr;

    static Node *merge(Node *t1, Node *t2) {
        if (!t1)
            return t2;
        if (!t2)
            return t1;
        if (t1->priority > t2->priority) {
            t1->right = merge(t1->right, t2);
            t1->update();
            return t1;
        } else {
            t2->left = merge(t1, t2->left);
            t2->update();
            return t2;
        }
    }

    static int getSize(Node*t) {
        if (!t) {
            return 0;
        }
        return t->count;
    }

    static void splitBySize(Node *t, int k, Node *&t1, Node *&t2) {
        if (!t) {
            t1 = t2 = nullptr;
            return;
        }
        if (k == 0) {
            t1 = nullptr;
            t2 = t;
            return;
        }
        int size = getSize(t->left) + 1;
        if (k < size) {
            if (t->left) {
                splitBySize(t->left, k, t1, t->left);
                t->update();
            }
            t2 = t;
        } else {
            if (t->right) {
                splitBySize(t->right, k - size, t->right, t2);
                t->update();
            }
            t1 = t;
        }
    }


    void destruct(Node *node) {
        if (!node) return;
        if (node->left) {
            destruct(node->left);
        }
        if (node->right) {
            destruct(node->right);
        }
        delete node;
    }

  public:
    void insert(int value, int position) {
        Node *less, *greater;
        splitBySize(root_, position, less, greater);
        less = merge(less, new Node(value, usingPriorities));
        root_ = merge(less, greater);
    }

    void remove(int position, int count) {
        Node *less, *equal, *greater;
        splitBySize(root_, position, less, greater);
        splitBySize(greater, position + count, equal, greater);
        root_ = merge(less, greater);
    }

    void remove(int position) {
       remove(position, 1);
    }

    int sum(int from, int to) {
        Node *less, *equal, *greater;
        splitBySize(root_, from, less, greater);
        splitBySize(greater, to - from, equal, greater);
        int ans = equal->sum;
        root_ = merge(less, equal);
        root_ = merge(root_, greater);
        return ans;
    }

    ~ImplicitTreap() {
        //destruct(root_);
    }
};

void fullImplicitTreap(vector<int> array, ImplicitTreap& treap) {
    for(int i = 0; i < array.size(); ++i) {
        treap.insert(array[i], i);
    }
}

void test1() {
    ImplicitTreap imt = ImplicitTreap();
    int n = 7;
    vector<int> array = {5, 24, 42, 13, 99, 2, 17};
    fullImplicitTreap(array, imt);
    vector<int> sums = vector<int>(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        sums[i] = sums[i - 1] + array[i - 1];
        //assert(sums[i] == imt.sum(0, i));
    }

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            assert(sums[j] - sums[i] == imt.sum(i, j));
        }
    }
}
int main() {
    test1();
    ImplicitTreap array = ImplicitTreap();
    fullImplicitTreap({5, 24, 42, 13, 99, 2, 17}, array);
    cout << array.sum(0, 6) << "\n";
}
