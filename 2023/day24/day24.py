import shapely as sp
import shapely.geometry as sg

inputName = "test"
index = 0
nameDict = {}
shapeList = []

with open(inputName, "r") as file:
    for line in file:
        pos = line.split(" @ ")[0].split(", ")
        vel = line.split(" @ ")[1].split(", ")
        velPoint = []
        
        for i in range(0, len(pos)):
            pos[i] = int(pos[i])
            vel[i] = int(vel[i])
            velPoint.append(pos[i] + vel[i])
        
        line = sg.LineString([pos, velPoint])
        shapeList.append(line)
        nameDict[line] = index
        index += 1
        
for i in range(0, len(shapeList)):
    for j in range(i + 1, len(shapeList)):
        if shapeList[i].intersects(shapeList[j]):
            index1 = nameDict[shapeList[i]]
            index2 = nameDict[shapeList[j]]
            print(f"Intersection between {index1} and {index2}")