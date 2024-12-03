## Il était 6h et je suis pas un mec du python
import pprint
import itertools

list = []

with open ('input', 'r') as f:
    lines = f.readlines()
    for line in lines:
        line = line.strip()
        numbers = line.split(' ')
        pprint.pprint(numbers)
        for i in range(len(numbers)):
            numbers[i] = int(numbers[i])
        list.append(numbers)

def check_line(line):
    ok_line = 0
    increasing = False
    print(line)
    for i in range(len(line)- 1):
        first = line[i]
        second = line[i + 1]
        
        if second > first and i == 0:
            increasing = True
        if increasing:
            diff = second - first
            if 1 <= diff <= 3:
                ok_line += 1
        else:
            diff = first - second
            if 1 <= diff <= 3:
                ok_line += 1         
    if ok_line == len(line) - 1:
        return True
    else:
        return False

safe_2 = 0

for line in list:
    if check_line(line):
        safe_2 += 1
    else:
        for i in range(len(line)):
            new_line = line.copy()
            del new_line[i]
            if check_line(new_line):
                safe_2 += 1
                break

safe_1 = sum([1 for line in list if check_line(line)])

print(safe_1)
print(safe_2)
