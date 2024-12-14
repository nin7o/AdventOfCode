import copy
import pprint
import time
import numpy as np 
from sympy import symbols, Eq, solve

dict = []

x, y = symbols('x y', integer=True)

with open ('input', 'r') as f:
    data = f.readlines()
    a_x, a_y = 0, 0
    b_x, b_y = 0, 0
    c_x, c_y = 0, 0
    for i, line in enumerate(data):
        if (i+1)%4 == 1:
            a_x, a_y = data[i].split('A: X+')[1].split(', Y+')
            a_x, a_y = int(a_x), int(a_y)
        elif (i+1)%4 == 2:
            b_x, b_y = data[i].split('B: X+')[1].split(', Y+')
            b_x, b_y = int(b_x), int(b_y)
        elif (i+1)%4 == 3:
            c_x, c_y = data[i].split('e: X=')[1].split(', Y=')
            c_x, c_y = int(c_x), int(c_y)
            dict.append({'a': (a_x, a_y), 'b': (b_x, b_y), 'p': (c_x + 10000000000000, c_y + 10000000000000)})
            print(f"a: ({a_x}, {a_y}), b: ({b_x}, {b_y}), p: ({c_x}, {c_y})")
            
            
def dist(a, b, c):
    print(f"a: {a}, b: {b}, c: {c}")
    A  = np.array([[a[0], b[0]], [a[1], b[1]]])
    B = np.array([c[0], c[1]])
    sol = np.linalg.solve(A, B)
    x, y = sol[0], sol[1]
    eps = 0.0001
    print(f"x: {x}, y: {y}")
    if x < 0 or y < 0 or abs(x - round(x)) > eps or abs(y - round(y)) > eps:
        print("REJECTED")
        return 0
    x, y = round(x), round(y)
    return 3*x + y

print(sum([dist(d['a'], d['b'], d['p']) for d in dict]))