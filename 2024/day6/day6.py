import pprint
import itertools
import re
import time 
import copy

map = []
LEFT = (-1, 0)
RIGHT = (1, 0)
UP = (0, -1)
DOWN = (0, 1)

def turn_right(direction):
    if direction == LEFT:
        return UP
    elif direction == RIGHT:
        return DOWN
    elif direction == UP:
        return RIGHT
    elif direction == DOWN:
        return LEFT

with open ('inputnat', 'r') as f:
    data = f.readlines()
    for line in data:
        map.append([char for char in line.strip()])
        
pos = copy.deepcopy(map)
man_coords = (0, 0)
man_dir = UP 

#find start 
for i, line in enumerate(map):
    for j, char in enumerate(line):
        if char == '^':
            man_coords = (j, i)
            
starting_coords = copy.deepcopy(man_coords)

while True:
    facing_obs_x = man_coords[0] + man_dir[0]
    facing_obs_y = man_coords[1] + man_dir[1]
    try:
        facing = map[facing_obs_y][facing_obs_x]
    except IndexError:
        break
    if facing == '#':
        man_dir = turn_right(man_dir)
    else:
        man_coords = (facing_obs_x, facing_obs_y)
        pos[facing_obs_y][facing_obs_x] = 'O'
        
first_map = copy.deepcopy(pos)
        
a = sum([line.count('O') for line in pos])
print("p1 : ",a)
print(first_map)

#p2
loop_count = 0

directions = copy.deepcopy(map)
for i, line in enumerate(directions):
    for j, char in enumerate(line):
        char = '.'
        
def check_dir(x, y, direction, directions):
    #print(f"checking {x}, {y} : {directions[y][x]} against {direction}")
    if directions[y][x] == '.':
        #print("first time at ", x, y)
        if direction == LEFT:
            directions[y][x] = '<'
        elif direction == RIGHT:
            directions[y][x] = '>'
        elif direction == UP:
            directions[y][x] = '^'
        elif direction == DOWN:
            directions[y][x] = 'v'
        return False
    elif direction == LEFT and directions[y][x] == '<':
        return True
    elif direction == RIGHT and directions[y][x] == '>':
        return True
    elif direction == UP and directions[y][x] == '^':
        return True
    elif direction == DOWN and directions[y][x] == 'v':
        return True
    return False
    

for y_obs, line in enumerate(map):
    print(f"y_obs: {y_obs}")
    for x_obs, char in enumerate(line):
        if char == '#' or char == '^' or not first_map[y_obs][x_obs] == 'O':
            continue
        else:
            pos = copy.deepcopy(map)
            directions_2 = copy.deepcopy(directions)
            man_dir = UP
            man_coords = copy.deepcopy(starting_coords)
            map[y_obs][x_obs] = '#'
            pos[y_obs][x_obs] = '#'
            #print(f"placing obstacle at {x_obs}, {y_obs}")
            loop = False
            while not loop:
                facing_obs_x = man_coords[0] + man_dir[0]
                facing_obs_y = man_coords[1] + man_dir[1]
                if facing_obs_x < 0 or facing_obs_y < 0 or facing_obs_x >= len(map[0]) or facing_obs_y >= len(map):
                    break
                facing = map[facing_obs_y][facing_obs_x]
                
                
                
                if facing == '#':
                    man_dir = turn_right(man_dir)
                else:
                    man_coords = (facing_obs_x, facing_obs_y)
                    if pos[facing_obs_y][facing_obs_x] == 'O' and check_dir(facing_obs_x, facing_obs_y, man_dir, directions_2):
                        #print("looping at ", facing_obs_x, facing_obs_y)
                        #print("man_dir: ",man_dir)
                        #print("directions: ", directions_2[facing_obs_y][facing_obs_x])
                        loop = True
                    pos[facing_obs_y][facing_obs_x] = 'O'
            map[y_obs][x_obs] = '.'
            pos[y_obs][x_obs] = '.'
            if loop:
                loop_count += 1
                
print("p2 : ", loop_count)
            