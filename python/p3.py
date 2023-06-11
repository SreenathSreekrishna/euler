#https://projecteuler.net/problem=3
#Largest Prime Factor

n = 600851475143
while n!=1:
    for i in range(2,n+1):
        if n % i == 0:
            n = n//i
            break

print(i)
