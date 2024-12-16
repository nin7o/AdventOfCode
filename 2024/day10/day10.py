import copy
import pprint
import time
data = []

with open ('input', 'r') as f:
    truc = f.readlines()
    truc = [x.strip() for x in truc]
    for line in truc:
        ptitliste = []
        for c in line:
            try:
                ptitliste.append(int(c))
            except:
                ptitliste.append(8)
        data.append(ptitliste)

    
    
def follow_trail_p2(data, start_x, start_y):
    trail_score = 0
    x = start_x
    y = start_y
    high = data[y][x]
    neighbours = []
    if x > 0:
        neighbours.append((data[y][x-1], x-1, y))
    if x < len(data[y])-1:
        neighbours.append((data[y][x+1], x+1, y))
    if y > 0:
        neighbours.append((data[y-1][x], x, y-1))
    if y < len(data)-1:
        neighbours.append((data[y+1][x], x, y+1))
    if high == 8:
        for n in neighbours:
            if n[0] == 9:
                trail_score += 1
    else:
        for n in neighbours:
            if n[0] == high + 1:
                trail_score += follow_trail_p2(data, n[1], n[2])
    return trail_score

def follow_trail(data, start_x, start_y):
    x = start_x
    y = start_y
    high = data[y][x]
    neighbours = []
    summits = []
    if x > 0:
        neighbours.append((data[y][x-1], x-1, y))
    if x < len(data[y])-1:
        neighbours.append((data[y][x+1], x+1, y))
    if y > 0:
        neighbours.append((data[y-1][x], x, y-1))
    if y < len(data)-1:
        neighbours.append((data[y+1][x], x, y+1))
    if high == 8:
        for n in neighbours:
            if n[0] == 9 and n not in summits:
                summits.append(n)
    else:
        for n in neighbours:
            if n[0] == high + 1:
                for s in follow_trail(data, n[1], n[2]):
                    if s not in summits:
                        summits.append(s)
    return summits

    
summits = []
total_score = 0
    
for y in range(len(data)):
    for x in range(len(data[y])):
        if data[y][x] == 0:
            total_score += follow_trail_p2(data, x, y)
            for s in follow_trail(data, x, y):
                summits.append(s)

print("p1 :",len(summits))
print("p2 :", total_score)