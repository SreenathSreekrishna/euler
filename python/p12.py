#https://projecteuler.net/problem=12
#Highly Divisible Triangular Number

def getNumFactors(n):
    f = 1
    curr = -1
    pow = 1
    while n>1:
        for i in range(2,n+1):
            if n%i == 0:
                n //= i
                if i == curr:
                    pow+=1
                else:
                    if curr != -1:
                        f*=(pow+1)
                    pow = 1
                    curr = i
                break
    return f*(pow+1)

i = 1
while getNumFactors(i*(i+1)//2) <= 500:
    i+=1

print(i*(i+1)//2)