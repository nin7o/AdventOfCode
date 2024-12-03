import pprint

leftlist = []
rightlist = []
rightdict = {}

with open ('input', 'r') as f:
    lines = f.readlines()
    for line in lines:
        line = line.strip()
        left, right = line.split()
        leftlist.append(int(left))
        rightlist.append(int(right))
        if int(right) not in rightdict:
            rightdict[int(right)] = 1
        else:
            rightdict[int(right)] += 1

leftlist.sort()
rightlist.sort()

dist = sum([abs(rightlist[i] - leftlist[i]) for i in range(len(leftlist))])
sim = sum([num * rightdict[num] for num in leftlist if num in rightdict])

print("dist: ", dist)
print("sim: ", sim)
