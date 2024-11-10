#https://projecteuler.net/problem=7
#10001st Prime

import math

def isPrime(n):
    for i in range(2, math.ceil(math.sqrt(n))+1):
        if n%i == 0:
            return False
    return True
n = 10001
i = 1
while n > 1:
    i+=1
    if isPrime(i):
        n -= 1

print(i)