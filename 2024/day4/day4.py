import pprint
import itertools
import re

lines = []
columns = []
diagonals_lr = []
diagonals_rl = []

with open ('input', 'r') as f:
    data = f.readlines()
    data = [line.strip() for line in data]
    lines = [line for line in data]
    diagonals_lr = [[] for _ in range(len(data) * 2 - 1)]
    diagonals_rl = [[] for _ in range(len(data) * 2 - 1)]
    columns = [[] for _ in range(len(data[0]))]
    for i, line in enumerate(data):
        for j, char in enumerate(line):
            #print(f"i: {i} j: {j} char: {char}")
            columns[j].append(char)
            num_diag_rl = i + j
            diagonals_rl[num_diag_rl].append(char)
            num_diag_lr = i - j
            diagonals_lr[num_diag_lr].append(char)

lines = [''.join(line) for line in lines]
columns = [''.join(column) for column in columns]
diagonals_lr = [''.join(diag) for diag in diagonals_lr]
diagonals_rl = [''.join(diag) for diag in diagonals_rl]
diagonals_lr = diagonals_lr[len(lines):] + diagonals_lr[:len(lines)]

# Des mauvaises décisions ont été prises, c'est moche mais rigolo

all_lines = lines + columns + diagonals_lr + diagonals_rl
xmas_filter = r"XMAS"
samx_filter = r"SAMX"
a = sum([line.count(xmas_filter) for line in all_lines]) + sum([line.count(samx_filter) for line in all_lines])
all_filter = f"{xmas_filter}|{samx_filter}"

diagonals_lr = [diag.replace("SAM", "SOM") for i, diag in enumerate(diagonals_lr)]
diagonals_lr = [diag.replace("MAS", "MOS") for i, diag in enumerate(diagonals_lr)]
diagonals_rl = [diag.replace("SAM", "SOM") for i, diag in enumerate(diagonals_rl)]
diagonals_rl = [diag.replace("MAS", "MOS") for i, diag in enumerate(diagonals_rl)]

center_dict = {}

for i, diag in enumerate(diagonals_rl):
    for j, char in enumerate(diag):
        if char == "O":
            # y = j qd i <= len(columns) - 1
            # y = j + i - len(columns) + 1 qd i > len(columns) - 1
            y = j if i <= len(columns) - 1 else j + i - len(columns) + 1
            #x = i - j qd i <= len(columns) - 1
            #x = len(columns) - 1 - j qd i > len(columns) - 1
            x = i - j if i <= len(columns) - 1 else len(columns) - 1 - j
            center_dict[(x, y)] = char

for i, diag in enumerate(diagonals_lr):
    for j, char in enumerate(diag):
        if char == "O":
            #y = j qd i <= len(columns) - 1
            #y = j - len(columns) - 1 + i qd i > len(columns) - 1
            y = j if i <= (len(columns) - 1) else j - len(columns) + 1 + i
            #x = len(columns) - 1 - i + j qd i <= len(columns) - 1
            #x = j qd i > len(columns) - 1
            x = len(columns) - 1 - i + j if i <= len(columns) - 1 else j
            center_dict[(x, y)] = 'X' if (x, y) in center_dict else char

b = sum([1 for key, value in center_dict.items() if value == "X"])

pprint.pprint(diagonals_lr)

print("p1:",a)   
print("p2:",b)     