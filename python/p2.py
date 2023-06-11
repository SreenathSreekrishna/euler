#https://projecteuler.net/problem=2
#Even Fibonacci Numbers

a,b = 1,2
s = 2
k = -1
while b<4000000:
    tmp = a+b
    a=b
    b=tmp
    if b%2 == 0:
        s+=b
print(s)