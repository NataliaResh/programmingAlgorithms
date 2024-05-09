#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cassert>

using namespace std;

const size_t P = 1306717;

class BloomFilter {
    int size_;
    vector<int> array_;
    vector<int> hashesA_;
    vector<int> hashesB_;

    static const size_t sizeInt = sizeof(int) * 8;

    static string bin(int n) {
        string ans = "";
        for (int i = 0; i < sizeInt; i++) {
            ans += to_string((n >> i) & 1);
        }
        return ans;
    }

    size_t hash(size_t x, size_t a, size_t b) {
        return ((a * x + b) % P) % size_;
    }

    void setBit(size_t i, size_t j) {
        array_[i] |= (1 << j);
    }

    bool getBit(size_t i, size_t j) {
        return (array_[i] >> j) & 1;
    }

public:
    BloomFilter(size_t s, float prError) {
        assert(prError > 0.0001f);
        if (prError == 0) throw;
        size_t b = ceil(-log2(prError) / log(2.0f));
        size_ = b * s;
        size_t k = -floor(log2(prError));
        array_ = vector<int>(((size_ + sizeof(int)) / sizeof(int) + 7) / 8, 0);
        hashesA_ = vector<int>(k);
        hashesB_ = vector<int>(k);

        for (size_t i = 0; i < k; i++) {
            hashesA_[i] = rand() % size_;
            hashesA_[i] = rand() % size_;
        }
        cout << "Size filter: " << size_ << "\nHash functions: " << k << "\n";
    }


    void insert(int ip) {
        for (size_t i = 0; i < hashesA_.size(); i++) {
            size_t h = hash(ip, hashesA_[i], hashesB_[i]);
            // cout << h << " " << h / sizeInt << " " << h % sizeInt << "\n";
            setBit(h / sizeInt, h % sizeInt);
        }
    }

    bool lookup(int ip) {
      // cout << "look\n";
        for (size_t i = 0; i < hashesA_.size(); i++) {
            size_t h = hash(ip, hashesA_[i], hashesB_[i]);
            if (!getBit(h / sizeInt, h % sizeInt))
// cout << h << " " << h / sizeInt << " " << h % sizeInt << "\n";
                return false;
        }
        return true;
    }

    string getFilter() {
        string ans = "";
        for (size_t i = 0; i < array_.size(); i++) {
            ans += bin(array_[i]);
        }
        return ans;
    }
};


int main() {
    srand(time(nullptr));
    int s;
    float prError;
    cout << "Requests: ";
    cin >> s;  // 8
    cout << "Probability: ";
    cin >> prError;  // 0.02
    BloomFilter bf = BloomFilter(s, prError);
    for (size_t i = 0; i < s; i++) {
        cout << "Insert new element " << i;
        if (bf.lookup(i)) {
            cout << " (not new)\n";
        } else {
            cout << "\n";
            bf.insert(i);
            if (bf.lookup(i)) {
                cout << "Now " << i << " in filter\n";
            }
        }
        cout << "BloomFilter: " << bf.getFilter() << "\n\n";
    }
}
