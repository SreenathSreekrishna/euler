#https://projecteuler.net/problem=5
#Smallest Multiple

def lcm(a, b):
   if a > b:
       n = a
   else:
       n = b
   while not (n % a == 0) or not (n % b == 0):
       n += 1
   return n

n = 20
l = 1
for i in range(1, n+1):
    l = lcm(l, i)

print(l)