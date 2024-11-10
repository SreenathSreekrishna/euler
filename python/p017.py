#https://projecteuler.net/problem=17
#Number Letter Counts

def getLetterCount(n):
    l = 0
    h = n // 100
    t = (n % 100) // 10
    o = n % 10
    teens = [3,6,6,8,8,7,7,9,8,8]
    t_ = [0,0,6,6,5,5,5,7,6,6]
    o_ = [0,3,3,5,4,4,3,5,5,4]
    if t == 1:
        l+=teens[o]
    else:
        l+=t_[t]
        l+=o_[o]
    if h:
        l+=(o_[h]+10)
    if not (o+t):
        l-=3
    return l

print(sum(getLetterCount(i) for i in range(1,1000))+len('onethousand'))