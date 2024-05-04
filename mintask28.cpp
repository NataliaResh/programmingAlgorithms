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
        return ((a * x) % P) % size_;
    }

    void setBit(size_t i, size_t j) {
        array_[i] |= (1 << j);
    }

    bool getBit(size_t i, size_t j) {
        return (array_[i] >> j) & 1;
    }

public:
    BloomFilter(size_t s, float prError) {
        if (prError == 0) throw;
        size_t b = round(-log2(prError) / log(2.0f));
        size_ = b * s;
        size_t k = -round(log2(prError));
        array_ = vector<int>(((size_ + sizeof(int) - 1) / sizeof(int) + 7) / 8, 0);
        hashes_ = vector<int>(k);
        for (size_t i = 0; i < k; i++) {
            hashes_[i] = rand() % size_;
        }
        cout << "Size filter: " << size_ << "\nHash functions: " << k << "\n";
    }


    void insert(int ip) {
        for (size_t i = 0; i < hashes_.size(); i++) {
            size_t h = hash(ip, hashes_[i]);
            setBit(h / sizeInt, h % sizeInt);
        }
    }

    bool lookup(int ip) {
        for (size_t i = 0; i < hashes_.size(); i++) {
            size_t h = hash(ip, hashes_[i]);
            if (!getBit(h / sizeInt, h % sizeInt))
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
