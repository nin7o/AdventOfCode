import math
import pprint
import shapely

filename = "input"

dictDir = {"0" : "R", "1" : "D", "2" : "L", "3" : "U"}

p1list = []
p2list = []

with open(filename, "r") as file:
    for line in file:
        templine = line.strip().split(" ")
        direction = templine[0]
        distance = int(templine[1])
        p1list.append([direction, distance])
        
        hexacode = templine[2][2:7]
        distance = int(hexacode, 16)
        direction = dictDir[templine[2][7]]
        p2list.append([direction, distance])


def day18(list):
    sommetList = []
    x = 0
    y = 0
    sommetList.append([x, y])
    for i in list:
        direction = i[0]
        distance = i[1]
        if direction == "R":
            x += distance
        elif direction == "L":
            x -= distance
        elif direction == "U":
            y += distance
        elif direction == "D":
            y -= distance
        sommetList.append([x, y])
        
    polygon = shapely.geometry.Polygon(sommetList).buffer(0.5, join_style="mitre")
    
    return polygon.area

print("part 1", day18(p1list))
print("part 2", day18(p2list))            