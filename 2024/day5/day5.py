import pprint
import itertools
import re
import random
import time 
import copy

rules = {}
inputs = []
rulesb = True

with open ('input', 'r') as f:
    data = f.readlines()
    for line in data:
        if line == '\n':
            rulesb = False
            continue
        if rulesb:
            rule = line.strip().split('|')
            if int(rule[0]) not in rules:
                rules[int(rule[0])] = [int(rule[1])]
            else:
                rules[int(rule[0])].append(int(rule[1]))
        else:
            inputs.append([int(i) for i in line.strip().split(',')])

#p1
def is_valid(rules, input):
    for left in rules:
        if left not in input:
            continue
        for right in rules[left]:
            if right not in input:
                continue
            if input.index(left) > input.index(right):
                return False
    return True

a = sum([input[int(len(input)/2)] for input in inputs if is_valid(rules, input)])
print("p1 : ",a)

#p2 - bogosort
global shuffle_counter
shuffle_counter = 0

def is_valid_bogo(rules, input):
    t1 = time.time()
    global shuffle_counter
    correct = True
    i = 0
    while not is_valid(rules, input):
        correct = False
        shuffle_counter += 1
        random.shuffle(input)
    t2 = time.time()
    print(f"Shuffle time: {t2 - t1}")
    if not correct:
        print(f"Shuffle counter: {shuffle_counter}")
        return input
    else:
        return [0]
    


#p2 - joli

def swap(input, a, b):
    input[a], input[b] = input[b], input[a]
    return input

def is_valid_joli(rules, input):
    inavlid = False
    
    i = 0
    while i < len(input):
        c = input[i]
        for ch in input[i+1:]:
            if ch in rules and c in rules[ch]:
                inavlid = True
                input = swap(input, i, input.index(ch))
                i -= 1
                break
        i += 1
    if inavlid:
        return input
    else:
        return [0]

boginputs = copy.deepcopy(inputs)

new_inputs = [is_valid_joli(rules, input) for input in inputs]
b = sum([input[int(len(input)/2)] for input in new_inputs])
print("p2 : ",b)

new_inputs = [is_valid_bogo(rules, input) for input in boginputs]
c = sum([input[int(len(input)/2)] for input in new_inputs])
print("p3 :",c)

                    