from math import *
from decimal import *
getcontext().prec = 5000000
a=Decimal(1.0)
b=Decimal(1/sqrt(2))
t=Decimal(0.25)
p=Decimal(1.0)
pi=Decimal(0)
_a=a
_b=b
_t=t
_p=p
n=int(input())
for i in range(1,n+1):
    _a=Decimal((a+b)/2)
    _b=Decimal(sqrt(a*b)) 
    _t=Decimal(t-p*((a-_a)**2))
    _p=Decimal(2*p)
    a=_a
    b=_b
    t=_t
    p=_p
    pi=Decimal(((a+b)**2)/(4*t))
with open("pi.txt","w") as file:
    file.write(str(pi))
#print(str(pi),"\n")
#高斯-勒让德算法
#最高精确到3.1415926535897931(小数点后15位)，精度问题
#https://zh.wikipedia.org/wiki/%E9%AB%98%E6%96%AF-%E5%8B%92%E8%AE%A9%E5%BE%B7%E7%AE%97%E6%B3%95
