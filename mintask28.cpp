#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

const size_t P = 1306717;

class BloomFilter {
  int size_;
  vector<int> array_;
  vector<int> hashes_;
  static const size_t sizeInt = sizeof(int) * 8;

  static string bin(int n) {
    string ans = "";
    for (int i = sizeInt - 1; i >= 0; i--) {
      ans += to_string((n >> i) & 1);
    }
    return ans;
  }
  size_t hash(size_t x, size_t a) {
      return (a * x % P) % size_;
  }

  void setOne(size_t i, size_t j) {
      size_t bit = 1 << j;
      array_[i] |= bit;
    }
  
  bool getOne(size_t i, size_t j) {
      return (array_[i] >> j) & 1;
    }

  public:
    BloomFilter(size_t s, float prError) {
      size_t b = round(-log2(prError) / log(2.0f));
      size_ = b * s;
      size_t k = -round(log2(prError));
      array_ = vector<int>(((size_ + sizeof(int) - 1) / sizeof(int) + 7) / 8, 0);
      hashes_ = vector<int>(k);
      for (size_t i = 0; i < k; i++) {
        hashes_[i] = rand() % size_;
      }
      cout << b << " " << array_.size() << " " << k << "\n";
    }
  
    
    void insert(int ip) {
      for (size_t i = 0; i < hashes_.size(); i++) {
        size_t h = hash(ip, hashes_[i]);
        setOne(h / sizeInt, h % sizeInt);
      }
    }

    bool lookup(int ip) {
      for (size_t i = 0; i < hashes_.size(); i++) {
        size_t h = hash(ip, hashes_[i]);
          if (!getOne(h / sizeInt, h % sizeInt))
            return false;
      }
      return true;
    }

    void printFilter() {
      for (size_t i = 0; i < array_.size(); i++) {
          cout << bin(array_[i]);
      }
      cout << "\n";
    }
};


int main() {
  BloomFilter bf = BloomFilter(8, 0.02);
  for (size_t i = 0; i < 100; i++) {
    bf.printFilter();
    cout << i << " "<< bf.lookup(i) << " ";
    bf.insert(i);
    cout << bf.lookup(i) << "\n";
  }
}
