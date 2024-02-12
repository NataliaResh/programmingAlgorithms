#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <locale>
#include <random>
#include <string>
#include <sys/types.h>
#include <vector>

using namespace std;

class LongNumber : public vector<char> {
public:
  bool negative = false;
  LongNumber() : vector<char>() {}
  LongNumber(size_t len) : vector<char>(len) {}
  LongNumber(size_t len, bool is_negative) : vector<char>(len){
    negative = is_negative;
  }
  void add_zeros(size_t count) {
    for (size_t i = 0; i < count; i++) {
      push_back(0);
    }
  }

  void add_zeros_back(size_t count) {
    reverse(begin(), end());
    add_zeros(count);
    reverse(begin(), end());
  }
  void delete_zeros() {
    while (size() > 1 && back() == 0) {
      pop_back();
    }
  }

  LongNumber copy() { return copy(0, size()); }

  LongNumber copy(size_t left, size_t right) {
    LongNumber new_number(right - left);
    for (size_t i = left; i < right; i++) {
      new_number[i - left] = at(i);
    }
    return new_number;
  }

  bool operator==(LongNumber &right) {
    if (size() != right.size()) {
      return false;
    }
    for (size_t i = 0; i < size(); i++) {
      if (at(i) != right[i]) {
        return false;
      }
    }
    return true;
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
    for (size_t i = 0; i < len; i++) {
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

  LongNumber operator*(LongNumber right) {
    vector<LongNumber> temp_res(right.size());
    for (size_t i = 0; i < right.size(); i++) {
      LongNumber temp(size());
      int pivot = 0;
      for (size_t j = 0; j < size(); j++) {
        int temp_mul = right[i] * at(j) + pivot;
        temp[j] = temp_mul % 10;
        pivot = (temp_mul - temp[j]) / 10;
      }
      if (pivot > 0) {
        temp.push_back(pivot);
      }
      temp.add_zeros_back(i);
      temp_res[i] = temp;
    }
    LongNumber res = temp_res[0];
    for (size_t i = 1; i < right.size(); i++) {
      res = res + temp_res[i];
    }
    res.delete_zeros();
    return res;
  }
};

LongNumber num_from_string(string str) {
  size_t len = str.size();
  bool negative = str[0] == '-';
  int end = 0;
  if (negative) {
    end++;
    len--;
  }
  LongNumber array(len, negative);
  for (int i = str.size() - 1; i >= end; i--) {
    array[i] = str[str.size() - 1 - i] - '0';
  }
  return array;
}

LongNumber kara_imp(LongNumber x, LongNumber y) {
  int n;
  if (x.size() > y.size()) {
    n = x.size();
    y.add_zeros(n - y.size());
  } else {
    n = y.size();
    x.add_zeros(n - x.size());
  }
  LongNumber res;
  if (n == 1) {
    int pivot = x[0] * y[0];
    res.push_back(pivot % 10);
    if (pivot > res[0]) {
      res.push_back(pivot / 10);
    }
    return res;
  }
  if (n & 1) {
    n += 1;
    y.add_zeros(1);
    x.add_zeros(1);
  }
  int len_b = n / 2;
  LongNumber a = x.copy(len_b, n);
  LongNumber b = x.copy(0, len_b);
  LongNumber c = y.copy(len_b, n);
  LongNumber d = y.copy(0, len_b);
  LongNumber ac = kara_imp(a, c);
  LongNumber bd = kara_imp(b, d);
  LongNumber theird = kara_imp(a + b, c + d);
  LongNumber ad_plus_bc = (theird - bd) - ac;
  ac.add_zeros_back(n);
  ad_plus_bc.add_zeros_back(len_b);
  res = ac + ad_plus_bc + bd;
  res.delete_zeros();
  return res;
}

LongNumber kara(LongNumber a, LongNumber b) {
  LongNumber res = kara_imp(a, b);
  if ((a.negative && !b.negative) || (!a.negative && b.negative)) {
    res.negative = true;
  }
  return res;
}

int main(int argc, char *argv[]) {
  LongNumber a, b;
  a = num_from_string("1234");
  b = num_from_string("5678");
  assert(kara(a, b) == a * b);

  a = num_from_string("1");
  b = num_from_string("10");
  assert(kara(a, b) == (a * b));

  a = num_from_string("-654321");
  b = num_from_string("101");
  assert(kara(a, b) == a * b);

  a = num_from_string("12345");
  b = num_from_string("0");
  assert(kara(a, b) == a * b);

  a = num_from_string("-7");
  b = num_from_string("-8");
  assert(kara(a, b) == a * b);

  a = num_from_string("1234567890987654321");
  b = num_from_string("987654321123456789");
  assert(kara(a, b) == a * b);

  a = num_from_string("1234565478987654345432344321");
  b = num_from_string("5678876545432345987654");
  assert(kara(a, b) == a * b);

  a = num_from_string("98546826024568732548542958656457");
  b = num_from_string("23456000034567236300000000000028");
  assert(kara(a, b) == a * b);

  a = num_from_string("12");
  b = num_from_string("-56728");
  assert(kara(a, b) == a * b);

  return 0;
}
