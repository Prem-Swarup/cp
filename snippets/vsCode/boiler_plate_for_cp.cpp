#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
#pragma GCC optimize("O2")
#include<bits/stdc++.h>
using namespace std;

#define deb cerr
#define i128 __int128 ;
#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int,int>
#define pll pair<long long, long long>
#define pb push_back
#define pf push_front
#define ppb pop_back
#define ppf pop_front
#define mk make_pair
#define fr(n) for(ll indx = 0; indx < n; indx++)
#define fri(ind, n) for(ll ind = 0; ind < n; ind++)
#define fc(itt, aa, bb) for(auto itt =  aa; itt < bb; itt++)
#define fa(itt, aa, bb) for(auto itt = aa; itt != bb; itt++)
#define fx(x,ax) for(auto &x:ax) 
#define wt while(true)
#define IOS ios_base :: sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define MOD 1000000007
#define MD2 998244353
#define MD3 100000000019
#define MD4 (1ll<<61)-1
#define vpl vector<pair<long long, long long>>
#define stl set<long long> 
#define ql queue<long long>
#define fi first
#define se second
#define all(x) x.begin(), x.end()
#define rd(x) ll x; cin>>x
#define rdl(...) ll __VA_ARGS__; read(__VA_ARGS__);
#define ra(x, n) ll x[n]; fri(iii, n) cin>>x[iii] 
#define rs(ssss) string ssss; cin>>ssss; 
#define rv(v, t, n) vector<t> v(n); fri(iiii, n) cin>>v[i] 
#define nl cout<<"\n" ;
#define lb lower_bound
#define ub upper_bound
#define mxe max_element
#define mne min_element
#define accm accumulate
#define br break ;
#define cnu continue ;
#define ump unordered_map
#define pq priority_queue
#define yy cout<<"YES" ; 
#define nn cout<<"NO" ; 
#define nnn cout<<-1 ; 
#define prans cout<<ans;
#define re return
#define flush cout.flush() ;
#define mmt memset
#define cnt_bt __builtin_popcount
#define cnt_btl __builtin_popcountll


typedef vector<int> vi;
typedef vector<long long> vll;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
 
template<typename T>
using oset = tree<T, null_type,less<T>, rb_tree_tag,tree_order_statistics_node_update>;
 

template<typename T>
void read(T& zz) {
    cin >> zz;
}

template<typename T, typename... Args>
void read(T& xy, Args&... args) {
    cin >> xy;
    read(args...);
}

template<typename T>
void prt(const T& xy) {
    cout << xy;
}

template<typename T, typename... Args>
void prt(const T& xy, const Args&... args) {
    cout << xy << ' ';
    prt(args...);
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    size_t szz = vec.size()-1;
    for (size_t i=0; i < szz; ++i) {
        os << vec[i] << ' '; 
    }
    if(szz>=0) os << vec.back();
    return os;
}

template<typename T, typename U>
std::ostream& operator<<(std::ostream& os, const std::pair<T, U>& prr) {
    os << prr.first << ' ' << prr.second;
    return os;
}


template<typename T>
std::istream& operator>>(std::istream& is, std::vector<T>& vec) {
    for (auto& item : vec) {
        is >> item; 
    }
    return is;
}

template<typename T, typename U>
std::istream& operator>>(std::istream& is, std::pair<T, U>& prr) {
    is >> prr.first >> prr.second;
    return is;
}


///////////////// MOD //////////////////////
const ll prm1=MOD ;

long long binPow(long long a, long long b) {
    a %= prm1;
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % prm1;
        a = a * a % prm1;
        b >>= 1;
    }
    return res;
}

class Mint {
public:
    long long n;
    long long prime1;

    Mint(long long num): prime1(prm1), n(num) {}

    Mint(long long num, long long prime) : n(num), prime1(prime) {}

    Mint(){
        prime1 = prm1;
        n = 0;
    }

    long long getNum() const {
        return n;
    }

    long long getPrime() const {
        return prime1;
    }

    Mint operator+(const Mint& other) const {
        return Mint((n + other.n) % prime1, prime1);
    }

    Mint operator-(const Mint& other) const {
        return Mint((n - other.n + prime1) % prime1, prime1);
    }

    Mint operator+(const ll other) const {
        return Mint((n + other) % prime1, prime1);
    }

    Mint operator-(const ll other) const {
        return Mint((n - other + prime1) % prime1, prime1);
    }

    Mint operator*(const Mint& other) const {
        return Mint((n * other.n) % prime1, prime1);
    }

    Mint operator*(const ll other) const {
        return Mint((n*other)%prime1, prime1);
    }

    Mint operator/(const Mint& other) const {
        long long inverse = modInverse(other.n, prime1);
        return Mint((n * inverse) % prime1, prime1);
    }
    Mint operator/(const ll other) const {
        long long inverse = modInverse(other, prime1);
        return Mint((n * inverse) % prime1, prime1);
    }

    Mint operator^(long long power) const {
        return power > 0 ? binExp(n, power, prime1) : Mint(1, prime1);
    }
    Mint operator^(Mint other) const {
        return other.n > 0 ? binExp(n, other.n, prime1) : Mint(1, prime1);
    }

    Mint operator+=(const Mint &other) {
        (*this) = (*this)+other;
        return *this;
    }
    
    Mint operator-=(Mint other) {
        (*this) = (*this)-other;
        return (*this) ;
    }
    
    Mint operator*=(Mint other) {
        *this = (*this)*other;
        return *this;
    }

    Mint operator/=(Mint other) {
        *this = (*this)/other;
        return *this;
    }

    Mint operator^=(ll other) {
        *this = (*this)^other;
        return (*this);
    }

    Mint operator^=(Mint other) {
      *this = (*this)^other;
      return *this;
    }

    Mint operator+=(ll other) {
        *this = (*this)+other;
        return *this;
    }

    Mint operator-=(ll other) {
        *this = (*this)-other;
        return *this;
    }
    
    Mint operator*=(ll other) {
        *this = (*this)*other;
        return *this;
    }
    
    Mint operator/=(ll other) {
        *this = (*this)/other;
        return *this;
    }    

private:
    long long modInverse(long long a, long long m) const {
        long long m0 = m, t, q;
        long long x0 = 0, x1 = 1;

        if (m == 1)
            return 0;

        while (a > 1) {
            q = a / m;

            t = m;

            m = a % m;
            a = t;

            t = x0;

            x0 = x1 - q * x0;

            x1 = t;
        }

        if (x1 < 0)
            x1 += m0;

        return x1;
    }

    Mint binExp(long long base, long long exp, long long mod) const {
        Mint result(1, mod);
        while (exp > 0) {
            if (exp % 2 == 1)
                result = (result * base);
            base = (base * base) % mod;
            exp /= 2;
        }
        return result;
    }
};

std::ostream& operator<<(std::ostream& os, const Mint& obj) {
    os << obj.n;
    return os;
}


Mint nCr(Mint n, Mint r) {
    if(r.n>n.n) return 0;
    r.n=min(r.n,n.n-r.n) ;
    
    if(r.n==0) return 1 ;
    
    Mint ans=1 ;
    
    for(ll i=0; i<r.n; i++) {
        ans = ans*(n-i);
        ans = ans/(i+1);
    }
    
    return ans;
}



/// @brief ///////////////////////////////
struct Roots {
  ld x1;
  ld x2;
  int numRoots;
};

Roots solveQuadratic(ld a, ld b, ld c) {
  Roots roots;
  ld discriminant = b * b - 4 * a * c;

  if (discriminant > 0) {
      roots.numRoots = 2;
      roots.x1 = (-b + sqrt(discriminant)) / (2 * a);
      roots.x2 = (-b - sqrt(discriminant)) / (2 * a);
  } else if (discriminant == 0) {
      roots.numRoots = 1;
      roots.x1 = -b / (2 * a);
      roots.x2 = roots.x1;
  } else {
      roots.numRoots = 0;
  }

  return roots;
}


 
/////////////////////////////////////////////////

void solve() {
    rdl(n) ;



    re ;
}

signed main() {
    IOS ;
    int t=1 ;
    cin>>t ;
    
    while(t--) {
        solve() ;
        cout<<"\n" ;
    }
    

    return 0;
}
