import sys

map = []
energyMap = []
visitedTiles = []

with open("input", "r") as file:
    for line in file:
        row = line.strip()
        lineLength = len(row)
        energyRow = []
        for i in range(lineLength):
            energyRow.append(0)
            
        energyMap.append(energyRow)
        map.append(row)
        
def nextTile(previousx, previousy, x, y):
    if (x, y, previousx, previousy) in visitedTiles:
        return
    if x < 0 or x >= len(map[0]) or y < 0 or y >= len(map):
        return
    visitedTiles.append((x, y, previousx, previousy))
    energyMap[y][x] = 1
    currentTile = map[y][x]
    match currentTile:
        case ".":
            diffx = x - previousx
            diffy = y - previousy
            nextx = x + diffx
            nexty = y + diffy
            nextTile(x, y, nextx, nexty)
            
        case "|":
            diffx = x - previousx
            diffy = y - previousy
            if diffx == 0:
                nextx = x + diffx
                nexty = y + diffy
                nextTile(x, y, nextx, nexty)
            else:
                nextx1 = x
                nexty1 = y + 1
                nextx2 = x
                nexty2 = y - 1
                nextTile(x, y, nextx1, nexty1)
                nextTile(x, y, nextx2, nexty2)
                
        case "-":
            diffx = x - previousx
            diffy = y - previousy
            if diffy == 0:
                nextx = x + diffx
                nexty = y + diffy
                nextTile(x, y, nextx, nexty)
            else:
                nextx1 = x + 1
                nexty1 = y
                nextx2 = x - 1
                nexty2 = y
                nextTile(x, y, nextx1, nexty1)
                nextTile(x, y, nextx2, nexty2)
                
        case "/":
            diffx = x - previousx
            diffy = y - previousy
            if diffx == 1:
                nextx = x
                nexty = y - 1
            elif diffx == -1:
                nextx = x
                nexty = y + 1
            elif diffy == 1:
                nextx = x - 1
                nexty = y
            elif diffy == -1:
                nextx = x + 1
                nexty = y
            nextTile(x, y, nextx, nexty)
                
        case "\\":
            diffx = x - previousx
            diffy = y - previousy
            if diffx == 1:
                nextx = x
                nexty = y + 1
            elif diffx == -1:
                nextx = x
                nexty = y - 1
            elif diffy == 1:
                nextx = x + 1
                nexty = y
            elif diffy == -1:
                nextx = x - 1
                nexty = y
            nextTile(x, y, nextx, nexty)
                
        case _:
            print("Error")
            
sys.setrecursionlimit(1000000)
print(sys.getrecursionlimit())
nextTile(-1, 0, 0, 0)
# add up energyMap
totalEnergy = 0
for row in energyMap:
    for tile in row:
        totalEnergy += tile
print("part 1 :",totalEnergy)

# Part 2 find the max total energy by starting from each border tile
maxEnergy = 0
for i in range(len(map[0])):
    energy = 0
    energyMap = []
    visitedTiles = []
    for row in map:
        energyRow = []
        for k in range(len(row)):
            energyRow.append(0)
        energyMap.append(energyRow)
    nextTile(i, -1, i, 0)
    
    for row in energyMap:
        for tile in row:
            energy += tile
    if energy > maxEnergy:
        maxEnergy = energy
        
print("up finished")

for i in range(len(map[0])):
    energy = 0
    energyMap = []
    visitedTiles = []
    for row in map:
        energyRow = []
        for k in range(len(row)):
            energyRow.append(0)
        energyMap.append(energyRow)
    nextTile(i, len(map), i, len(map) - 1)
    
    for row in energyMap:
        for tile in row:
            energy += tile
    if energy > maxEnergy:
        maxEnergy = energy
        
print("down finished")
    
for i in range(len(map)):
    energy = 0
    energyMap = []
    visitedTiles = []
    for row in map:
        energyRow = []
        for k in range(len(row)):
            energyRow.append(0)
        energyMap.append(energyRow)
    nextTile(-1, i, 0, i)
    
    for row in energyMap:
        for tile in row:
            energy += tile
    if energy > maxEnergy:
        maxEnergy = energy
    
print("left finished")
    
for i in range(len(map)):
    energy = 0
    energyMap = []
    visitedTiles = []
    for row in map:
        energyRow = []
        for k in range(len(row)):
            energyRow.append(0)
        energyMap.append(energyRow)
    nextTile(len(map[0]), i, len(map[0]) - 1, i)
    
    for row in energyMap:
        for tile in row:
            energy += tile
    if energy > maxEnergy:
        maxEnergy = energy
print("right finished")

print("part 2: ", maxEnergy)
             