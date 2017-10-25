import numpy as np

def check_for_zero(e, n):
    if e == 0:
        print(n, "is the gcd")
    else:
        print(e, "is the gcd")

def check_EEA(e, n, r, ee, ea):
    if( (e * ee) + ( n * ea) == r):
        return 1
    else:
        return 0

e=int(input("Enter E "))
n=int(input("Enter N "))

print("(" + str(e) + ", " + str(n) + ")")
     
while e != 0 or n !=0:
    try:
        temp = n%e
        print("(" + str(e) + ", " + str(temp) + ")")
        n=temp
        temp = e%n
        print("(" + str(temp) + ", " + str(n) + ")")
        e = temp
    except ZeroDivisionError:
        check_for_zero(e,n)
        break
