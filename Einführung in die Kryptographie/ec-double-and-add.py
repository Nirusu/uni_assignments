# -*- coding: utf-8 -*-
import math


def mod_inv(x):
    # we use a prime modulo anyway, so let's use simple math™ instead of EEA
    return pow(x, p - 2, p)


# p1 and p2 are Python tuples, where p1[0] is x1 and p1[1] is y1. Same goes for p2 where p2[0] = x2 and p2[1) = y2
def double(p1):
    s = ((3 * pow(p1[0], 2) + a) * mod_inv(2 * p1[1])) % p
    x3 = (pow(s, 2) - 2 * p1[0]) % p
    y3 = (s * (p1[0] - x3) - p1[1]) % p
    return x3, y3


def add(p1, p2):
    # special check for neutral element
    inv_y1 = -p1[1] % p
    if p1[0] == p2[0] and -p1[1] % p == inv_y1:
        # math.inf is the neutral element
        return math.inf
    else:
        s = ((p2[1] - p1[1]) * mod_inv(p2[0] - p1[0])) % p
        x3 = (pow(s, 2) - p1[0] - p2[0]) % p
        y3 = (s * (p1[0] - x3) - p1[1]) % p
        return x3, y3


print("Bitte geben Sie die Parameter der elliptischen Kurve ein:")
a = int(input("a = "))
b = int(input("b = "))
p = int(input("p = "))
# check if the elliptic curve is actually usable
if ((4 * pow(a, 3) + 27 * pow(b, 2)) % p) == 0:
    print("Die Kurvenbedingung ist nicht erfüllt. Das Programm bricht ab.")
    exit()
# get user inputs
print("Bitte geben Sie den ersten Punkt an:")
x1 = int(input("x1 = "))
y1 = int(input("y1 = "))
print("Bitte geben Sie den zweiten Punkt an:")
x2 = int(input("x2 = "))
y2 = int(input("y2 = "))
# check if both points are the same. If yes, use the double function. If not, use the add function.
if (x1 == x2 and y1 == y2):
    result = double((x1, y1))
else:
    result = add((x1, y1), (x2, y2))
# check if the result is math.inf, our neat little workaround for the neutral object
if result == math.inf:
    print('O')
    print("Da das Ergebnis das neutrale Element ist, liegt der Punkt auf der Kurve.")
else:
    print(result)
    # check if point is on curve
    if pow(result[1], 2, p) == (pow(result[0], 3) + result[0] * a + b) % p:
        print("Der Punkt liegt auf der Kurve.")
    else:
        print("Der Punkt liegt NICHT auf der Kurve.")
