import copy
import pprint
import time
from collections import defaultdict
from functools import cache

field = []
hitmap = {}

with open ('test', 'r') as f:
    kayou = f.readlines()
    for line in kayou:
        field.append(list(line.strip()))
        
def reset_hitmap():
    for i in range(len(field)):
        for j in range(len(field[0])):
            hitmap[i][j] = 0

hitmap = copy.deepcopy(field)
reset_hitmap()
len_x = len(field)
len_y = len(field[0])

def find_fence_size(x, y, field_size = 0, corner_num = 0):
    field_size += 1
    fence_size = 0
    field_type = field[x][y]
    neighbors = []
    
    hitmap[x][y] = 1
    
    up, down, left, right = False, False, False, False
    
    if x > 0:
        neighbors.append((x-1, y))
        up = True
    if y > 0:
        neighbors.append((x, y-1))
        left = True
    if x < len_x-1:
        neighbors.append((x+1, y))
        down = True
    if y < len_y-1:
        neighbors.append((x, y+1))  
        right = True  
    if len(neighbors) < 4:
        fence_size += 4 - len(neighbors)
        
    
    for neighbor in neighbors:
        if not field[neighbor[0]][neighbor[1]] == field_type:
            fence_size += 1
        elif hitmap[neighbor[0]][neighbor[1]] == 0:
            truc = find_fence_size(neighbor[0], neighbor[1])
            fence_size += truc[0]
            field_size += truc[1]
            corner_num += truc[2]
            
    return [fence_size, field_size, corner_num]

total_fence_size = 0
p2 = 0

for i in range(len_x):
    for j in range(len_y):
        if hitmap[i][j] == 0:
            local_fence_size, local_field_size, size_num = find_fence_size(i, j)
            print(local_fence_size, local_field_size, size_num, field[i][j])
            total_fence_size += local_fence_size * local_field_size
            p2 += size_num * local_field_size
            
            
    
pprint.pprint(total_fence_size)
print(p2)