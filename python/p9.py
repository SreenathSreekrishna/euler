#https://projecteuler.net/problem=9
#Special Pythagorean Triplet

from random import randint
while True:
    a = randint(0,1000)
    b = randint(0,1000-a)
    c = 1000-a-b
    if a*a+b*b==c*c and a!=0 and b!=0 and c!=0:
        break
print(a*b*c)