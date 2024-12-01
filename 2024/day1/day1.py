import pprint

leftlist = []
rightlist = []
rightdict = {}

with open ('input', 'r') as f:
    lines = f.readlines()
    for line in lines:
        line = line.strip()
        left, right = line.split('   ')
        leftlist.append(int(left))
        rightlist.append(int(right))
        if int(right) not in rightdict:
            rightdict[int(right)] = 1
        else:
            rightdict[int(right)] += 1

leftlist.sort()
rightlist.sort()
total_dist = 0
total_similarities = 0

for i, num in enumerate(leftlist):
    distance = abs(rightlist[i] - leftlist[i])
    total_dist += distance
    if num in rightdict:
        total_similarities += num * rightdict[num]

print("total_dist: ", total_dist)
print("total_similarities: ", total_similarities)
