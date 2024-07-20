import math
import pprint
import networkx as nx

inputName = "test"
nodeList = []
matrix = []

startNode = (0, 0)
endNode = (0, 0)

graphDict = {}

with open(inputName, "r") as file:
    for line in file:
        lineList = []
        for char in line:
            if char == "\n":
                continue
            lineList.append(char)
        matrix.append(lineList)
        
for y in range(len(matrix)):
    for x in range(len(matrix[y])):
        if x >= 1 and x <= len(matrix[y]) - 2 and y >= 1 and y <= len(matrix) - 2:
            numOfNeigthbours = 0
            if matrix[y][x-1] == "^" or matrix[y][x-1] == ">" or matrix[y][x-1] == "<" or matrix[y][x-1] == "v":
                numOfNeigthbours += 1
            if matrix[y][x+1] == "^" or matrix[y][x+1] == ">" or matrix[y][x+1] == "<" or matrix[y][x+1] == "v":
                numOfNeigthbours += 1
            if matrix[y-1][x] == "^" or matrix[y-1][x] == ">" or matrix[y-1][x] == "<" or matrix[y-1][x] == "v":
                numOfNeigthbours += 1
            if matrix[y+1][x] == "^" or matrix[y+1][x] == ">" or matrix[y+1][x] == "<" or matrix[y+1][x] == "v":
                numOfNeigthbours += 1
            if numOfNeigthbours >= 3:
                nodeList.append((x, y))
        elif y == 0 and matrix[y][x] == ".":
            startNode = (x, y)
            nodeList.append((x, y))
        elif y == len(matrix) - 1 and matrix[y][x] == ".":
            endNode = (x, y)
            nodeList.append((x, y))

    
def checkNeighbours(coords):
    x = coords[0]
    y = coords[1]
    if coords in nodeList:
        return coords
    if matrix[y][x-1] != "#":
        return (x-1, y)
    if matrix[y][x+1] != "#":
        return (x+1, y)
    if matrix[y-1][x] != "#":
        return (x, y-1)
    if matrix[y+1][x] != "#":
        return (x, y+1)
    return None
            
print(nodeList, len(nodeList))

for node in nodeList:
    if node == startNode or node == endNode:
        continue
    nodeDict = {}
    if matrix[node[1] - 1][node[0]] == "^":
            xtemp = node[0]
            ytemp = node[1] - 1
            distance = 2
            matrix[ytemp][xtemp] = "X"
            while (newCoords := checkNeighbours((xtemp, ytemp))) not in nodeList:
                xtemp = newCoords[0]
                ytemp = newCoords[1]
                distance += 1
                matrix[ytemp][xtemp] = "X"
            print(node, distance, newCoords)
            nodeDict[newCoords] = distance
    if matrix[node[1] + 1][node[0]] == "v":
            xtemp = node[0]
            ytemp = node[1] + 1
            distance = 2
            matrix[ytemp][xtemp] = "X"
            while (newCoords := checkNeighbours((xtemp, ytemp))) not in nodeList:
                xtemp = newCoords[0]
                ytemp = newCoords[1]
                distance += 1
                matrix[ytemp][xtemp] = "X"
            print(node, distance, newCoords)
            nodeDict[newCoords] = distance
    if matrix[node[1]][node[0] - 1] == "<":
            xtemp = node[0] - 1
            ytemp = node[1]
            distance = 2
            matrix[ytemp][xtemp] = "X"
            while (newCoords := checkNeighbours((xtemp, ytemp))) not in nodeList:
                xtemp = newCoords[0]
                ytemp = newCoords[1]
                distance += 1
                matrix[ytemp][xtemp] = "X"
            print(node, distance, newCoords)
            nodeDict[newCoords] = distance
    if matrix[node[1]][node[0] + 1] == ">":
            xtemp = node[0] + 1
            ytemp = node[1]
            distance = 2
            matrix[ytemp][xtemp] = "X"
            while (newCoords := checkNeighbours((xtemp, ytemp))) not in nodeList:
                xtemp = newCoords[0]
                ytemp = newCoords[1]
                distance += 1
                matrix[ytemp][xtemp] = "X"
            print(node, distance, newCoords)
            nodeDict[newCoords] = distance
    graphDict[node] = nodeDict
    
pprint.pprint(graphDict)
            