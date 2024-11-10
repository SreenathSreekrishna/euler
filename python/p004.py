#https://projecteuler.net/problem=4
#Largest Palindrome Product

import math
def palindromic(n):
    s = str(n)
    l = len(s)
    return s[:math.floor(l/2)][::-1] == s[math.ceil(l/2):]

for i in range(999, 900, -1):
    for j in range(999, 900, -1):
        if palindromic(i*j):
            print(i*j)
            exit(0)