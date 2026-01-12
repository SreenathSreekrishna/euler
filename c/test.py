# A160599_tests.py
# Multiple algorithms to find composite n with (n - phi(n)) | (n-1)
# Run all three algorithms up to N_test and compare results, and compare to OEIS known initial terms.

import math, random, time
from collections import Counter

N_test = 2*10**11

# Deterministic Miller-Rabin for 64-bit
def is_prime(n):
    if n < 2:
        return False
    small = [2,3,5,7,11,13,17,19,23,29]
    for p in small:
        if n % p == 0:
            return n == p
    d = n-1
    s = 0
    while d % 2 == 0:
        d //= 2
        s += 1
    bases = [2, 325, 9375, 28178, 450775, 9780504, 1795265022]
    def check(a):
        x = pow(a, d, n)
        if x == 1 or x == n-1:
            return True
        for _ in range(s-1):
            x = (x*x) % n
            if x == n-1:
                return True
        return False
    for a in bases:
        if a % n == 0:
            return True
        if not check(a):
            return False
    return True

# Pollard-Rho
def pollard_rho(n):
    if n % 2 == 0:
        return 2
    if is_prime(n):
        return n
    while True:
        c = random.randrange(1, n-1)
        x = random.randrange(2, n-1)
        y = x
        d = 1
        while d == 1:
            x = (x*x + c) % n
            y = (y*y + c) % n
            y = (y*y + c) % n
            d = math.gcd(abs(x-y), n)
            if d == n:
                break
        if 1 < d < n:
            return d

def factor(n):
    n = int(n)
    if n == 1:
        return []
    if is_prime(n):
        return [n]
    d = pollard_rho(n)
    if d == n:
        # fallback
        for p in range(3, int(math.isqrt(n))+1, 2):
            if n % p == 0:
                d = p
                break
    return factor(d) + factor(n//d)

def divisors_from_factors(factors):
    from collections import Counter
    cnt = Counter(factors)
    ds = [1]
    for p,e in cnt.items():
        cur = []
        powp = 1
        for i in range(e+1):
            for x in ds:
                cur.append(x * powp)
            powp *= p
        ds = cur
    return sorted(ds)

# Linear sieve for phi and primes
def linear_sieve_phi(n):
    phi = [0]*(n+1)
    primes = []
    is_comp = [False]*(n+1)
    phi[1] = 1
    for i in range(2, n+1):
        if phi[i] == 0:
            phi[i] = i-1
            primes.append(i)
        for p in primes:
            v = i*p
            if v > n:
                break
            is_comp[v] = True
            if i % p == 0:
                phi[v] = phi[i]*p
                break
            else:
                phi[v] = phi[i]*(p-1)
    return phi, primes, is_comp

# Algorithm A: brute-force phi check (composites only)
start = time.time()
phi, primes_list, is_comp = linear_sieve_phi(N_test)
algA = []
for n in range(4, N_test+1):
    if not is_comp[n]:
        continue
    d = n - phi[n]
    if d != 0 and (n-1) % d == 0:
        algA.append(n)
endA = time.time()

# Algorithm B: semiprime factor-M reduction
startB = time.time()
limit_p = int(math.isqrt(N_test))
primes_small = [p for p in primes_list if p <= limit_p]
algB = []
seenB = set()
for p in primes_small:
    M = p*p - p + 1
    facs = factor(M)
    ds = divisors_from_factors(facs)
    for d in ds:
        if d <= p:
            continue
        q = d - p + 1
        if q < p:
            continue
        if p*q > N_test:
            continue
        if is_prime(q):
            n = p*q
            if n not in seenB and n >= 4:
                seenB.add(n)
                algB.append(n)
endB = time.time()

# Algorithm C: iterate prime pairs (direct, but bounded)
startC = time.time()
algC = []
seenC = set()
for i,p in enumerate(primes_small):
    for q in primes_list[i:]:
        if p*q > N_test:
            break
        n = p*q
        d = n - (p-1)*(q-1)
        if d !=0 and (n-1) % d == 0:
            if n >= 4 and not is_comp[n]:
                # should be composite, sanity
                pass
            if n not in seenC:
                seenC.add(n)
                algC.append(n)
endC = time.time()

algA_sorted = sorted(algA)
algB_sorted = sorted(algB)
algC_sorted = sorted(algC)

# Known OEIS initial composite terms (taken from OEIS A160599)
oeis_initial = [15,85,255,259,391,589,1111,3193,4171,4369,12361,17473,21845,25429,28243,47989,52537,65535,65641,68377,83767,91759,100777,120019,144097,167743,186367,268321,286357,291919,316171,327937,335923,346063,353029]

# Compare
A_set = set(algA_sorted)
B_set = set(algB_sorted)
C_set = set(algC_sorted)

common_AB = sorted(A_set & B_set)
common_ABC = sorted(A_set & B_set & C_set)

# mismatches vs OEIS initial
miss_A = [x for x in oeis_initial if x <= N_test and x not in A_set]
miss_B = [x for x in oeis_initial if x <= N_test and x not in B_set]
miss_C = [x for x in oeis_initial if x <= N_test and x not in C_set]

print(f"N_test = {N_test}")
print(f"Algorithm A found {len(algA_sorted)} composite solutions; time {endA-start:.3f}s")
print(f"Algorithm B found {len(algB_sorted)} composite semiprime solutions; time {endB-startB:.3f}s")
print(f"Algorithm C (pair enumeration) found {len(algC_sorted)} composite semiprime solutions; time {endC-startC:.3f}s")
print("First 40 from A:", algA_sorted[:40])
print("First 40 from B:", algB_sorted[:40])
print("First 40 from C:", algC_sorted[:40])
print("Common A&B count:", len(common_AB))
print("Common A&B&C count:", len(common_ABC))
print("OEIS initial terms <= N_test missing in A:", miss_A)
print("OEIS initial terms <= N_test missing in B:", miss_B)
print("OEIS initial terms <= N_test missing in C:", miss_C)

print(sum(algA_sorted))