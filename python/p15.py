#https://projecteuler.net/problem=15
#Lattice Paths

from math import factorial as f
n = 20
print(f(n*2) // f(n) // f(n))