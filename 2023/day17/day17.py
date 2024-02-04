import math
import pprint
from datetime import datetime

input = "input"

horizontalDict = {}
verticalDict = {}

inputMatrix = []
idMatrix = []

reach = 3

id = 0
with open(input, "r") as file:
    for line in enumerate(file):
        matrixline = []
        idline = []
        for char in line[1]:
            if char != "\n":
                matrixline.append(int(char))
                id += 1
                idline.append(id)
        inputMatrix.append(matrixline)
        idMatrix.append(idline)
        
x_size = len(inputMatrix[0])
y_size = len(inputMatrix)

# horizzontal graoh creation
for y in range(y_size):
    for x in range(x_size):
        dictionary = {}
        distance = 0
        for i in range (x - 1, x - reach - 1, -1):
            if i >= 0 and i < x_size:
                distance += inputMatrix[y][i]
                id = (str(idMatrix[y][i]) + "V")
                dictionary[id] = distance
        distance = 0
        for i in range (x + 1, x + reach + 1):
            if i >= 0 and i < x_size:
                distance += inputMatrix[y][i]
                id = (str(idMatrix[y][i]) + "V")
                dictionary[id] = distance
        horizontalDict[str(idMatrix[y][x]) + "H"] = dictionary

print("Horizontal graph created")

# vertical graoh creation
for x in range(x_size):
    for y in range(y_size):
        dictionary = {}
        distance = 0
        for i in range (y - 1, y - reach - 1, -1):
            if i >= 0 and i < y_size:
                distance += inputMatrix[i][x]
                id = (str(idMatrix[i][x]) + "H")
                dictionary[id] = distance
        distance = 0
        for i in range (y + 1, y + reach + 1):
            if i >= 0 and i < y_size:
                distance += inputMatrix[i][x]
                id = (str(idMatrix[i][x]) + "H")
                dictionary[id] = distance
        verticalDict[str(idMatrix[y][x]) + "V"] = dictionary

print("Vertical graph created")

#concatenate the two dictionaries
graph = {**horizontalDict, **verticalDict}

#dijkstra


class Dijkstra:
    def __init__(self, graph, start_vertex):
        self.graph = graph;
        self.start_vertex = start_vertex
        self.vertices = list(graph.keys())

        # distance: minimum distance from start vertex
        self.vertex_labels = {vertex: {'distance': math.inf, 'prev': '-'} for vertex in self.vertices}

        # Obviously, the start vertex has no distance from itself
        self.vertex_labels[start_vertex]['distance'] = 0


    def _get_edge_weight(self, vertex1, vertex2):
        try:
            return self.graph[vertex1][vertex2]
        except KeyError:
            return math.inf


    def _set_label(self, vertex, weight, prev=''):
        self.vertex_labels[vertex]['distance'] = weight

        if prev:
            self.vertex_labels[vertex]['prev'] = prev


    def _get_label(self, vertex):
        return self.vertex_labels[vertex]


    def dijkstra(self):
        interiors = [self.start_vertex]
        max_interior_vertices = len(self.vertices)

        while True:
            exteriors = [vertex for vertex in self.vertices if vertex not in interiors]

            # Nearest vertex to start vertex
            nearest_vertex = '-'

            # Distance from start index
            nearest_vertex_distance = math.inf

            for exterior in exteriors:
                exterior_label = self._get_label(exterior)

                # Shortest discovered distance of current outerior from start vertex
                shortest_discovered_distance = exterior_label['distance']

                # Last vertex through which we reached current exterior with shortest distance
                choosen_prev = exterior_label['prev']

                for interior in interiors:
                    # Shortest discovered distance of current interior from start vertex + distance of current interior from current exterior
                    distance_from_exterior = self._get_label(interior)['distance'] + self._get_edge_weight(interior, exterior)

                    if distance_from_exterior < shortest_discovered_distance:
                        shortest_discovered_distance = distance_from_exterior
                        choosen_prev = interior
            
                self._set_label(exterior, shortest_discovered_distance, choosen_prev)

                # Attempt to find the nearest exterior to start vertex
                if shortest_discovered_distance < nearest_vertex_distance:
                    nearest_vertex_distance = shortest_discovered_distance
                    nearest_vertex = exterior
            
            interiors.append(nearest_vertex)

            if len(interiors) == max_interior_vertices:
                print("All vertices are interior vertices")
                break

            # Print statement to show progress
            remaining_nodes = max_interior_vertices - len(interiors)
            print(f"{remaining_nodes} nodes left to compute")


    def build_path(self, vertex):
        if vertex == '-':
            return []
        
        return self.build_path(self.vertex_labels[vertex]['prev']) + [vertex]
    
# add the entry node to the graph
tempdict = {}
tempdict["1H"] = 0
tempdict["1V"] = 0

graph["START"] = tempdict

dijkstra = Dijkstra(graph, start_vertex="START")

dijkstra.dijkstra()



endvertexH = str(idMatrix[y_size-1][x_size-1]) + "H"
endvertexV = str(idMatrix[y_size-1][x_size-1]) + "V"

print(f"Shortest path to end vertex: {dijkstra.build_path(endvertexH)}")
print(f"Shortest path to end vertex: {dijkstra.build_path(endvertexV)}")

#print vertex label for end vertex
print(f"Shortest path to end vertex: {dijkstra._get_label(endvertexH)}")
print(f"Shortest path to end vertex: {dijkstra._get_label(endvertexV)}")