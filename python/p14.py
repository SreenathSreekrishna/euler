#https://projecteuler.net/problem=14
#Longest Collatz Sequence

def collatz(n):
    #returns length of sequence starting with n
    l = 0
    while n != 1:
        if n%2 == 0:
            n//=2
        else:
            n = 3*n+1
        l+=1
    return l

vals = [collatz(i) for i in range(1, 1000000)]
print(vals.index(max(vals))+1)