import copy
import pprint

antennas = {}
antinodes = {}
antinodes_2 = {}

def symetrique(xa, ya, xb, yb):
    xc = 2*xb - xa
    yc = 2*yb - ya
    return (xc, yc)

def symetrique_2(xa, ya, xb, yb):
    all_sym = []
    all_sym.append((xa, ya))
    all_sym.append((xb, yb))
    while True:
        xc = 2*xb - xa
        yc = 2*yb - ya
        if xc < 0 or xc >= x_len or yc < 0 or yc >= y_len:
            break
        all_sym.append((xc, yc))
        xa, ya = xb, yb
        xb, yb = xc, yc
    return all_sym

with open ('input', 'r') as f:
    data = f.readlines()
    x_len = len(data[0].strip())
    y_len = len(data)
    for y, line in enumerate(data):
        for x, char in enumerate(line.strip()):
            if char != '.':
                if antennas.get(char):
                    antennas[char].append((x, y))
                else:
                    antennas[char] = [(x, y)]
    
# P1                
for key in antennas:
    antennes = antennas[key]
    if len(antennes) == 1:
        continue
    for ant in antennes:
        for other_ant in antennes:
            if ant == other_ant:
                continue
            x, y = ant
            other_x, other_y = other_ant
            sym = symetrique(x, y, other_x, other_y)
            x_sym, y_sym = sym
            if x_sym >= 0 and x_sym < x_len and y_sym >= 0 and y_sym < y_len:
                antinodes[sym] = True
                
# P2
for key in antennas:
    antennes = antennas[key]
    if len(antennes) == 1:
        continue
    for ant in antennes:
        for other_ant in antennes:
            if ant == other_ant:
                continue
            x, y = ant
            other_x, other_y = other_ant
            syms = symetrique_2(x, y, other_x, other_y)
            for sym in syms:
                antinodes_2[sym] = True
                
#write a map with antinodes to the terminal
for y in range(y_len):
    for x in range(x_len):
        if antinodes_2.get((x, y)):
            print('X', end='')
        else:
            print('.', end='')
    print()

print(len(antinodes))
#pprint.pprint(antinodes_2)
print(len(antinodes_2))        
    