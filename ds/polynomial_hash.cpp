#include<bits/stdc++.h>
using namespace std;



class PolynomialHash {
public:
    PolynomialHash(long long arr[], int sz, long long p = 31, long long m = 1e9 + 9) 
        : p(p), m(m), size(sz), hashValues(size + 1, 0), pPow(size + 1, 1) {
        
        for (size_t i = 0; i < size; ++i) {
            hashValues[i + 1] = (hashValues[i] + (arr[i] % m) * pPow[i]) % m;
            pPow[i + 1] = (pPow[i] * p) % m;
        }
    }

    long long hash(int l, int r) const {
        assert(l >= 0 && r < size);
        long long hashValue = (hashValues[r + 1] - hashValues[l] + m) % m;
        long long power = pPow[l];
        return (hashValue * modInverse(power, m)) % m;
    }

private:
    long long p, m;
    size_t size;
    std::vector<long long> hashValues, pPow;

    long long modInverse(long long a, long long m) const {
        long long result = 1, power = m - 2; 
        while (power) {
            if (power % 2) {
                result = (result * a) % m;
            }
            a = (a * a) % m;
            power /= 2;
        }
        return result;
    }
};


class RollingHash {
public:
    RollingHash(string ss, long long p = 31, long long m = 1e9 + 9) 
        : p(p), m(m), size(ss.length()), hashValues(size + 1, 0), pPow(size + 1, 1) {
        for (size_t i = 0; i < size; ++i) {
            hashValues[i + 1] = (hashValues[i] + (ss[i]-'a') * pPow[i]) % m;
            pPow[i + 1] = (pPow[i] * p) % m;
        }
    }

    long long hash(int l, int r) const {
        assert(l >= 0 && r < size);
        long long hashValue = (hashValues[r + 1] - hashValues[l] + m) % m;
        long long power = pPow[l];
        return (hashValue * modInverse(power, m)) % m;
    }

private:
    long long p, m;
    size_t size;
    std::vector<long long> hashValues, pPow;

    long long modInverse(long long a, long long m) const {
        long long result = 1, power = m - 2; 
        while (power) {
            if (power % 2) {
                result = (result * a) % m;
            }
            a = (a * a) % m;
            power /= 2;
        }
        return result;
    }
};



// examples
void solve() {
    int n, q;
    cin>>n>>q;
    long long arr[n];
    for(int i=0; i<n; ++i) cin>>arr[i];
    PolynomialHash hsh(arr, n);
    
    for(int i=0; i<q; ++i) {
        int l, r;
        cin>>l>>r;
        cout<<hsh.hash(l,r)<<endl;
    }
    string s;
    cin>>s>>q;
    RollingHash shsh(s);
    for(int i=0; i<q; ++i) {
        int l, r;
        cin>>l>>r;
        cout<<shsh.hash(l,r)<<endl;
    }

}
signed main() {
  int t;
  cin>>t;
  while(t--) {
    solve();
  }
  return 0;
}
