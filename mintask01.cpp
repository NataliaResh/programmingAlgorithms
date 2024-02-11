#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class LongNumber : public vector<char> {
public:
  LongNumber() : vector<char>() {}
  LongNumber(size_t len) : vector<char>(len) {}
  void add_zeros(int count) {
    for (size_t i = 0; i < count; i++) {
      push_back(0);
    }
  }

  void delete_zeros() {
    while (back() == 0 && size() > 1) {
      pop_back();
    }
  }

  LongNumber copy() { return copy(0, size()); }

  LongNumber copy(size_t left, size_t right) {
    LongNumber new_number(right - left);
    for (size_t i = left; i < right; i++) {
      new_number[i] = at(i);
    }
    return new_number;
  }

  bool operator<(LongNumber &right) {
    if (size() != right.size()) {
      return size() < right.size();
    }
    for (int i = size() - 1; i >= 0; i--) {
      if (at(i) != right[i]) {
        return at(i) < right[i];
      }
    }
    return false;
  }

  bool operator<=(LongNumber &right) { return *this < right || *this == right; }

  LongNumber operator+(LongNumber right) {
    int len;
    if (size() > right.size()) {
      len = size();
      right.add_zeros(len - right.size());
    } else {
      len = right.size();
      add_zeros(len - size());
    }
    LongNumber res(len);
    int pivot = 0;
    for (int i = 0; i < len; i++) {
      int temp_sum = at(i) + right[i] + pivot;
      res[i] = temp_sum % 10;
      pivot = (temp_sum - res[i]) / 10;
    }
    if (pivot > 0) {
      res.push_back(pivot);
    }
    return res;
  }

  LongNumber operator-(LongNumber right) {
    LongNumber res = copy();
    for (size_t i = 0; i < right.size(); i++) {
      if (res[i] >= right[i]) {
        res[i] -= right[i];
      } else {
        size_t j = i + 1;
        while (res[j] == 0) {
          res[j] = 9;
          j++;
        }
        res[j]--;
        res[i] += 10 - right[i];
      }
    }
    res.delete_zeros();
    return res;
  }
};

void print_int(LongNumber &array) {
  for (int i = array.size() - 1; i >= 0; i--) {
    cout << (char)(array[i] + '0');
  }
  cout << "\n";
}

LongNumber input_int(int len) {
  LongNumber array(len);
  for (int i = len - 1; i >= 0; i--) {
    char temp;
    cin >> temp;
    array[i] = temp - '0';
  }
  return array;
}

void division_imp(LongNumber &a, LongNumber &b, LongNumber &c,
                  LongNumber &pivot) {
  if (a.size() == 0) {
    return;
  }
  pivot.insert(pivot.begin(), a.back()); // m
  a.pop_back();                          // 1
  int res = 0;
  LongNumber temp = b.copy(); // m
  for (; temp <= pivot; res++) {
    temp = temp + b; // m
  }
  c.insert(c.begin(), res);     // (n - m)
  pivot = pivot - (temp - b);   // m
  division_imp(a, b, c, pivot); // n
}

LongNumber division(LongNumber a, LongNumber b) {
  LongNumber c, pivot = {};
  division_imp(a, b, c, pivot);
  c.delete_zeros();
  return c;
}

int main() {
  int n, m;
  cin >> n >> m;
  LongNumber a = input_int(n), b = input_int(m);
  LongNumber c = division(a, b);
  print_int(c);
  return 0;
}
