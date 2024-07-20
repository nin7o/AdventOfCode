import networkx as nx
import pprint as pp
import matplotlib.pyplot as plt

fileName = "input"
G = nx.Graph()
graph = {}

with open(fileName, "r") as f:
    for line in f:
        linkList = []
        for i in range(int((len(line.strip()) - 4 ) / 4)):
            linkList.append(line.strip()[5 + 4*i: 5 + 4*i + 3])
        pp.pprint(linkList)
        graph[line.strip()[:3]] = linkList
            
G.add_nodes_from(graph.keys())
for key in graph.keys():
    for link in graph[key]:
        G.add_edge(key, link)

#nx.draw(G, with_labels=True)
#plt.show()
#links to remove found visually lol

G.remove_edge("zvk", "sxx")
G.remove_edge("pbx", "njx")
G.remove_edge("sss", "pzr")

print(nx.number_connected_components(G))
print([len(c) for c in sorted(nx.connected_components(G), key=len, reverse=True)])
print([len(c) for c in sorted(nx.connected_components(G), key=len, reverse=True)][0] * [len(c) for c in sorted(nx.connected_components(G), key=len, reverse=True)][1])
        