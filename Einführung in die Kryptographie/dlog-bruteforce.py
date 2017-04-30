# -*- coding: utf-8 -*-
p = int(input("p = "))
alpha = int(input("alpha = "))
beta = int(input("beta = "))
x = alpha
counter = 1
while x != beta:
    x = x * alpha % p
    counter += 1
print(counter)

# Lösung für c): 19637