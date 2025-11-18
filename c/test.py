from math import floor

MAX_A = 999_999          # largest odd a allowed
C_MAX = 50_000_000       # upper bound for c = b/2

def build_spf(n):
    spf = [0]*(n+1)
    for i in range(2, n+1):
        if spf[i]==0:
            spf[i]=i
            if i*i <= n:
                for j in range(i*i, n+1, i):
                    if spf[j]==0:
                        spf[j] = i
    spf[1] = 1
    return spf

def distinct_prime_factors(x, spf):
    primes = []
    while x > 1:
        p = spf[x]
        primes.append(p)
        while x % p == 0:
            x //= p
    return list(dict.fromkeys(primes))

def count_coprime_in_range(L, R, primes):
    if L > R:
        return 0
    total = R - L + 1
    excluded = 0
    m = len(primes)
    from itertools import combinations
    for k in range(1, m+1):
        for comb in combinations(primes, k):
            prod = 1
            for p in comb:
                prod *= p
                if prod > R:
                    break
            if prod > R:
                continue
            cnt = R//prod - (L-1)//prod
            if k % 2 == 1:
                excluded += cnt
            else:
                excluded -= cnt
    return total - excluded

def compute_total_pairs():
    spf = build_spf(MAX_A)
    total = 0
    for a in range(1, MAX_A+1, 2):   # iterate odd a
        primes = distinct_prime_factors(a, spf)
        L = 50*a + 1
        R = C_MAX
        total += count_coprime_in_range(L, R, primes)
    return total

if __name__ == "__main__":
    print(compute_total_pairs())
