import pprint
import copy

inputName = "input"

nbOfSteps = 64
currentMap = [] 
nextMap = []
blankMap = []

def checkNeighbours(x, y):
    if x >= 0 and y >= 0 and y < len(currentMap) and x < len(currentMap[y]):
        if currentMap[y][x] == ".":
            return True
        
def removeoFromMap(map):
    for y in range(len(map)):
        for x in range(len(map[y])):
            if map[y][x] == "o":
                map[y][x] = "."
                
def countoInMap(map):
    count = 0
    for y in range(len(map)):
        for x in range(len(map[y])):
            if map[y][x] == "o":
                count += 1
    return count
        

with open(inputName, "r") as f:
    for line in f:
        linelist = []
        for char in line:
            if char != "\n":
                if char == "S":
                    char = "o"
                linelist.append(char)
        currentMap.append(linelist)
        
blankMap = copy.deepcopy(currentMap)
removeoFromMap(blankMap)
        
print("len y |")
pprint.pprint(len(currentMap))
print("len x -")
pprint.pprint(len(currentMap[0]))
print("Blank Map")
pprint.pprint(blankMap)
print("current Map")
pprint.pprint(currentMap)
nextMap = copy.deepcopy(currentMap)
        
for i in range(nbOfSteps):
    nextMap = copy.deepcopy(blankMap)
    print("Step: ", i)
    print("next map :")
    pprint.pprint(nextMap)
    print("iterating through this map :")
    pprint.pprint(currentMap)
    for y in range(len(currentMap)):
        for x in range(len(currentMap[y])):
            state = currentMap[y][x]
            if state == "o":
                print("found o at ", x, y)
                leftx, lefty = x-1, y
                rightx, righty = x+1, y
                upx, upy = x, y-1
                downx, downy = x, y+1
                if checkNeighbours(leftx, lefty):
                    nextMap[lefty][leftx] = "o"
                if checkNeighbours(rightx, righty):
                    nextMap[righty][rightx] = "o"
                if checkNeighbours(upx, upy):
                    nextMap[upy][upx] = "o"
                if checkNeighbours(downx, downy):
                    nextMap[downy][downx] = "o"
    print("final next map")
    pprint.pprint(nextMap)
    currentMap = copy.deepcopy(nextMap)
    print("final current map")
    pprint.pprint(currentMap)
    print("count of o in current map")
    pprint.pprint(countoInMap(currentMap))
    
 
#write final map to file
with open("output", "w") as f:
    for y in range(len(currentMap)):
        for x in range(len(currentMap[y])):
            f.write(currentMap[y][x])
        f.write("\n")                   