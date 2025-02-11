from math import *
import sys

# https://oj.vnoi.info/problem/nd_thpt_2021_a

def ptich(n):
    if n == 1: return 0
    ans = 0
    for i in range(1, int(sqrt(n)) + 1):
        if(n%i==0):
            ans+=i
            if (n//i != i):
                ans+=n//i
    return ans

def main():
    n = int(input())
    a = []
    ans = 0
    for i in range(n):
        x = int(input())
        # print(ptich(x))
        if x*2 <= ptich(x):
            a.append(x)
            ans+=1    
    print(ans)
    for i in a:
        print(i)
      
sys.stdin = open("GHH.INP", "r")
sys.stdout = open("GHH.OUT", "w")
main()