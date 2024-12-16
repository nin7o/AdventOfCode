import copy
import pprint
import time
from collections import defaultdict
from functools import cache

kayou = []
kayoud = {}

with open ('input', 'r') as f:
    kayou = f.read().strip().split(' ')
    kayou = [int(x) for x in kayou]
    
print(kayou)
for kayouu in kayou:
    kayoud[kayouu] = 1

def blink(kayou):
    i = 0
    while i < len(kayou):
        if kayou[i] == 0:
            kayou[i] = 1
        elif len(str(kayou[i]))%2 == 0:
            num_str = str(kayou[i])
            left_half = num_str[:len(num_str)//2]
            right_half = num_str[len(num_str)//2:]
            kayou[i] = int(left_half)
            kayou.insert(i+1, int(right_half))
            i += 1
        else:
            kayou[i] = kayou[i] * 2024
        i += 1

def blink_fast_af(kayoud):
    new_kayoud = defaultdict(int)
    for key in kayoud:
        if key == 0:
            new_kayoud[1] += kayoud[key]
        elif len(str(key))%2 == 0:
            num_str = str(key)
            left_half = num_str[:len(num_str)//2]
            right_half = num_str[len(num_str)//2:]
            new_kayoud[int(left_half)] += kayoud[key]
            new_kayoud[int(right_half)] += kayoud[key]
        else:
            new_kayoud[key * 2024] += kayoud[key]
    kayoud.clear()
    kayoud.update(new_kayoud)

#P1
for i in range(25):
    blink(kayou)
    print("blink", i)

print("p1 :", len(kayou))

#P2
for i in range(75):
    blink_fast_af(kayoud)
    #print("blink", i)

print(kayoud)
print("p2 :", sum([kayoud[x] for x in kayoud]))