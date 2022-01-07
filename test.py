import networkx as nx
import matplotlib.pyplot as plt
import sys


#utility function that returns the minimum egde weight node
def minDistance(dist, mstSet, V):
    min = sys.maxsize
    for v in range(V):
        if mstSet[v] == False and dist[v] < min:
            min = dist[v]
            min_index = v
    return min_index 

#function that performs prims algorithm on the graph G
def prims(G, pos):
	V = len(G.nodes()) # V denotes the number of vertices in G
	dist = [] # dist[i] will hold the minimum weight edge value of node i to be included in MST
	parent = [None]*V # parent[i] will hold the vertex connected to i, in the MST edge
	mstSet = [] # mstSet[i] will hold true if vertex i is included in the MST
	#initially, for every node, dist[] is set to maximum value and mstSet[] is set to False
	for i in range(V):
		dist.append(sys.maxsize)
		mstSet.append(False)
	dist[0] = 0
	parent[0]= -1 #starting vertex is itself the root, and hence has no parent
	for count in range(V-1):
		u = minDistance(dist, mstSet, V) #pick the minimum distance vertex from the set of vertices
		mstSet[u] = True
		#update the vertices adjacent to the picked vertex
		for v in range(V):
			if (u, v) in G.edges():
				if mstSet[v] == False and G[u][v]['length'] < dist[v]:
					dist[v] = G[u][v]['length']
					parent[v] = u
	for X in range(V):
		if parent[X] != -1: #ignore the parent of the starting node
			if (parent[X], X) in G.edges():
				nx.draw_networkx_edges(G, pos, edgelist = [(parent[X], X)], width = 2.5, alpha = 0.6, edge_color = 'r')
	return



#takes input from the file and creates a weighted graph
def CreateGraph():
    G = nx.Graph
    f = open('input.txt')
    n = int(f.readline())
    wMatrix = []
    for i in range(n):
        list1 = f.readline().split()
        list1 = [int(u) for u in list1]
        wMatrix.append(list1)
    for i in range(n):
        for j in range(n)[i:] :
            if wMatrix[i][j] > 0:
                G.add_edge(i, j, length = wMatrix[i][j])
    return G

#draws the graph and displays the weights on the edges
def DrawGraph(G):
	pos = nx.spring_layout(G)
	nx.draw(G, pos, with_labels = True)  #with_labels=true is to show the node number in the output graph
	edge_labels = nx.get_edge_attributes(G,'length')
	nx.draw_networkx_edge_labels(G, pos, edge_labels = edge_labels, font_size = 11) #prints weight on all the edges
	return pos



#main function
if __name__ == "__main__":
	G = CreateGraph()
	pos = DrawGraph(G)
	prims(G, pos)
	plt.show()