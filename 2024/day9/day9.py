import copy
import pprint
import time

line = []

with open ('input', 'r') as f:
    data = f.read().strip()
    line = list(data)
    line = [int(x) for x in line]


def build_line(line):
    new_line = []
    is_bloc = True
    bloc_index = 0
    for i in range(len(line)):
        if is_bloc:
            for j in range(line[i]):
                new_line.append(bloc_index)
            is_bloc = False
        else:
            for j in range(line[i]):
                new_line.append(-1)
            is_bloc = True
            bloc_index += 1
    return new_line


def fix_line(line):
    i = 0
    while i < len(line):
        if line[i] == -1:
            while line[-1] == -1:
                line.pop()
            line[i] = line[-1]
            line.pop()
        i += 1
    return line

def find_end_bloc_size(line, start=len(line)-1):
    #print("finding end bloc size from", start, ":", line[start])
    i = start
    while line[i] == -1:
        i -= 1
    l = 0
    while line[i] == line[i-l]:
        l += 1
    #print("end bloc size is", l)
    return l

def find_enough_free_space(line, bloc_size):
    #print("looking for enough free space for bloc of size", bloc_size)
    try:
        i = 0
        size = 0
        while size < bloc_size:
            while line[i] != -1:
                i += 1
                size = 0
            while line[i] == -1:
                i += 1
                size += 1
        #print("found enough free space at", i - size)
        return i - size
    except:
        #print("no enough free space found")
        return -1
    
def fix_line_2(line):
    index_last_bloc = len(line) - 1
    while index_last_bloc > 0:
        if line[index_last_bloc] == -1:
            index_last_bloc -= 1
            continue
        #print(line)
        #print("last bloc is at", index_last_bloc, ":", line[index_last_bloc])
        end_bloc_size = find_end_bloc_size(line, index_last_bloc)
        enough_free_space = find_enough_free_space(line, end_bloc_size)
        if enough_free_space == -1:
            #print("no enough free space found, we do nothing")
            index_last_bloc -= end_bloc_size
        elif index_last_bloc < enough_free_space:
            #print("on ne recule pas le bloc")
            index_last_bloc -= end_bloc_size
        else:
            #print("moving bloc from", index_last_bloc - end_bloc_size, "to", enough_free_space)
            for i in range(end_bloc_size):
                line[enough_free_space + i], line[index_last_bloc - i] = line[index_last_bloc - i], line[enough_free_space + i]
            index_last_bloc -= end_bloc_size
    for i in range(len(line)):
        if line[i] == -1:
            line[i] = 0
    return line
        
        

#print("p1       :",compute_checksum(line))
line = build_line(line)
line1 = fix_line(line.copy())
line2 = fix_line_2(line.copy())
print("p1       :", sum([v * i for i, v in enumerate(line1)]))
print("p2       :", sum([v * i for i, v in enumerate(line2)]))
            
        
        
    
    