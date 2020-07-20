#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
using namespace std;

static const int BASE1 = 31;
static const int BASE2 = 67;
static const int PRIME_MODULUS1 = 1000000009;
static const int PRIME_MODULUS2 = 1000000007;

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1,T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);

        return h1 ^ h2;  
    }
};

string getSubstring(const string& s, int n, int k) {
    vector<long long> BASE1_pow(n);
    vector<long long> BASE2_pow(n);
    
    BASE1_pow[0] = 1;
    BASE2_pow[0] = 1;
    for (int i = 1; i < n; i++) {
        BASE1_pow[i] = (BASE1_pow[i-1] * BASE1) % PRIME_MODULUS1;
        BASE2_pow[i] = (BASE2_pow[i-1] * BASE2) % PRIME_MODULUS2;
    }

    vector<long long> hash1(n + 1, 0);
    vector<long long> hash2(n + 1, 0);
    for (int i = 0; i < n; i++) {
        hash1[i+1] = (hash1[i] + s[i] * BASE1_pow[i]) % PRIME_MODULUS1;
        hash2[i+1] = (hash2[i] + s[i] * BASE2_pow[i]) % PRIME_MODULUS2;
    }
        
    unordered_map<pair<int, int>, pair<int, int>, pair_hash> map;
    int counter = 0;
    int substringFirstInd = 0;
    
    for (int i = 0; i <= n - k; i++) {
        long long currentHash1 = (hash1[i + k] + PRIME_MODULUS1 - hash1[i]) % PRIME_MODULUS1;
        long long currentHash2 = (hash2[i + k] + PRIME_MODULUS2 - hash2[i]) % PRIME_MODULUS2;
        currentHash1 = (currentHash1 * BASE1_pow[n - i - 1]) % PRIME_MODULUS1;
        currentHash2 = (currentHash2 * BASE2_pow[n - i - 1]) % PRIME_MODULUS2;
        
        pair<long long, long long> hashPair(currentHash1, currentHash2);
        auto it = map.find(hashPair);

        if (it == map.end()) {
            map.emplace(hashPair, make_pair(i, 1));
            if (counter == 0 || counter == 1) {
                substringFirstInd = i;
                counter = 1;
            }
        }
        else {
            it->second.second++;
            if (it->second.second >= counter) {
                substringFirstInd = it->second.first;
                counter = it->second.second;
            }
        }
    }
    
    return s.substr(substringFirstInd, k);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, k;
    cin >> n >> k;
    cin.ignore();

    string text;
    getline(cin, text);
    
    cout << getSubstring(text, n, k);

    return 0;
}
