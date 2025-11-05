// pe180_fixed2.cpp
// g++ -std=c++17 -O2 pe180_fixed2.cpp -o pe180

#include <iostream>
#include <vector>
#include <numeric>
using namespace std;
using i128 = __int128_t;

struct Frac {
    i128 p;
    i128 q;
    Frac(): p(0), q(1) {}
    Frac(i128 P, i128 Q): p(P), q(Q) { normalize(); }
    void normalize(){
        if (q == 0) { p = 0; q = 1; return; }
        if (q < 0) { p = -p; q = -q; }
        i128 a = p >= 0 ? p : -p;
        i128 b = q >= 0 ? q : -q;
        // gcd for i128
        if (a == 0) { q = 1; p = 0; return; }
        i128 x = a, y = b;
        while (y != 0) { i128 t = x % y; x = y; y = t; }
        i128 g = x;
        if (g == 0) { q = 1; p = 0; return; }
        p /= g; q /= g;
    }
};

static i128 as_i128(long long v){ return (i128)v; }

Frac add(const Frac &A, const Frac &B){
    i128 np = A.p * B.q + B.p * A.q;
    i128 nq = A.q * B.q;
    return Frac(np, nq);
}
Frac mul(const Frac &A, const Frac &B){
    return Frac(A.p * B.p, A.q * B.q);
}
int cmpFrac(const Frac &A, const Frac &B){
    i128 lhs = A.p * B.q;
    i128 rhs = B.p * A.q;
    if (lhs < rhs) return -1;
    if (lhs > rhs) return  1;
    return 0;
}

string toString(i128 v){
    if (v == 0) return "0";
    bool neg = v < 0;
    if (neg) v = -v;
    string s;
    while (v > 0){
        int d = (int)(v % 10);
        s.push_back(char('0' + d));
        v /= 10;
    }
    if (neg) s.push_back('-');
    reverse(s.begin(), s.end());
    return s;
}
void printFrac(const Frac &f){
    cout << toString(f.p) << "/" << toString(f.q);
}

i128 isqrt_i128(i128 n){
    if (n <= 0) return 0;
    i128 lo = 0, hi = n;
    while (lo <= hi){
        i128 mid = (lo + hi) >> 1;
        i128 sq = mid * mid;
        if (sq == n) return mid;
        if (sq < n) lo = mid + 1;
        else hi = mid - 1;
    }
    return hi;
}
bool is_perfect_square_i128(i128 n, i128 &root){
    if (n < 0) return false;
    root = isqrt_i128(n);
    return root * root == n;
}

int main(){
    const int N = 35;
    vector<Frac> fracs;
    for (int b = 2; b <= N; ++b){
        for (int a = 1; a < b; ++a){
            if (std::gcd(a,b) != 1) continue;
            fracs.emplace_back(as_i128(a), as_i128(b));
        }
    }
    cout << "fracs count = " << fracs.size() << "\n";

    sort(fracs.begin(), fracs.end(), [](const Frac &A, const Frac &B){ return cmpFrac(A,B) < 0; });

    vector<Frac> raw_sums;
    for (size_t i = 0; i < fracs.size(); ++i){
        for (size_t j = i; j < fracs.size(); ++j){
            Frac x = fracs[i];
            Frac y = fracs[j];

            // n = 1: z = x + y must be a reduced proper fraction with denom <= N
            Frac z1 = add(x, y);
            if (z1.p > 0 && z1.q <= N && z1.p < z1.q){
                Frac s = add(add(x, y), z1);
                raw_sums.push_back(s);
            }

            // n = 2: check if x^2 + y^2 is a perfect square rational
            Frac x2 = mul(x, x);
            Frac y2 = mul(y, y);
            Frac sqsum = add(x2, y2);
            i128 a = sqsum.p;
            i128 b = sqsum.q;
            i128 ra = 0, rb = 0;
            if (a > 0 && b > 0 && is_perfect_square_i128(a, ra) && is_perfect_square_i128(b, rb)){
                Frac z2(ra, rb);
                if (z2.p > 0 && z2.q <= N && z2.p < z2.q){
                    Frac s = add(add(x, y), z2);
                    raw_sums.push_back(s);
                }
            }
        }
    }

    cout << "raw sums count = " << raw_sums.size() << "\n";
    if (raw_sums.empty()){
        cout << "No results\n";
        return 0;
    }

    sort(raw_sums.begin(), raw_sums.end(), [](const Frac &A, const Frac &B){ return cmpFrac(A,B) < 0; });
    vector<Frac> uniq;
    uniq.push_back(raw_sums[0]);
    for (size_t i = 1; i < raw_sums.size(); ++i){
        if (cmpFrac(raw_sums[i], uniq.back()) != 0) uniq.push_back(raw_sums[i]);
    }

    cout << "distinct s count = " << uniq.size() << "\n";
    // print the list (comment out if too verbose)
    for (auto &f : uniq){
        printFrac(f); cout << "\n";
    }

    // compute total
    Frac total(0,1);
    for (auto &f : uniq) total = add(total, f);

    cout << "sum t = "; printFrac(total); cout << "\n";
    cout << "u+v = " << toString(total.p + total.q) << "\n";
    return 0;
}
