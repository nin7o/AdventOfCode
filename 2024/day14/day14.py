import copy
import pprint
import time
import numpy as np
from scipy.spatial import distance

len_x = 101
len_y = 103

robots = []

with open ('input', 'r') as f:
    data = f.readlines()
    for line in data:
        pos, vel = line.split(' ')
        pos_x, pos_y = pos.split('=')[1].split(',')
        vel_x, vel_y = vel.split('=')[1].split(',')
        pos_x, pos_y, vel_x, vel_y = int(pos_x), int(pos_y), int(vel_x), int(vel_y)
        robots.append({'pos': (pos_x, pos_y), 'vel': (vel_x, vel_y)})

def move_robots(robots):
    new_robots = []
    for robot in robots:
        new_pos = ((robot['pos'][0] + robot['vel'][0]) % len_x, (robot['pos'][1] + robot['vel'][1]) % len_y)
        new_robots.append({'pos': new_pos, 'vel': robot['vel']})
    return new_robots

def longest_chain(points):
    def get_neighbors(point):
        x, y = point
        return [
            (x-1, y-1), (x, y-1), (x+1, y-1),
            (x-1, y),             (x+1, y),
            (x-1, y+1), (x, y+1), (x+1, y+1)
        ]

    def dfs(point, visited):
        stack = [point]
        length = 0
        while stack:
            current = stack.pop()
            if current not in visited:
                visited.add(current)
                length += 1
                for neighbor in get_neighbors(current):
                    if neighbor in points and neighbor not in visited:
                        stack.append(neighbor)
        return length

    points_set = set(points)
    visited = set()
    max_length = 0

    for point in points:
        if point not in visited:
            max_length = max(max_length, dfs(point, visited))

    return max_length

#print the robots in the grid 
def print_con():
    grid = [['.' for x in range(len_x)] for y in range(len_y)]
    for robot in robots:
        x, y = robot['pos']
        grid[y][x] = '#'

    for row in grid:
        print(''.join(row))

robots_100 = []
i = 0

for k in range(5000):
    robots = move_robots(robots)
    i += 1
    if i == 100:
        robots_100 = copy.deepcopy(robots)
    
while True:
    try:
        i += 1
        robots = move_robots(robots)
        
        if i % 1000 == 0:
            print(i)
        if longest_chain([robot['pos'] for robot in robots]) > 30:
            print_con()
            print(i)
            time.sleep(0.5)
    except KeyboardInterrupt:
        break
    
    
up_left = 0
up_right = 0
down_left = 0
down_right = 0

for robot in robots_100:
    if robot['pos'][0] < len_x//2 and robot['pos'][1] < len_y//2:
        up_left += 1
    elif robot['pos'][0] > len_x//2 and robot['pos'][1] < len_y//2:
        up_right += 1
    elif robot['pos'][0] < len_x//2 and robot['pos'][1] > len_y//2 :
        down_left += 1
    elif robot['pos'][0] > len_x//2 and robot['pos'][1] > len_y//2 :
        down_right += 1

        
print(up_left, up_right, down_left, down_right)
print(up_left * up_right * down_left * down_right)
