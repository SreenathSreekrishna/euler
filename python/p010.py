#https://projecteuler.net/problem=10
#Summation of Primes

import math

def isPrime(n):
    if n==2:
        return True
    for i in range(2, math.ceil(math.sqrt(n))+1):
        if n%i == 0:
            return False
    return True

print(sum(i for i in range(2,2000000) if isPrime(i)))
