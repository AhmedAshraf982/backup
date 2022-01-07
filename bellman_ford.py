import matplotlib.pyplot as plt
import networkx as nx

from numpy import *
from numpy import inf

#graph initializations:
G = nx.Graph()# for original graph
G2 = nx.Graph()# MST Tree 

# window = Tk()
# window.title("Graphs")
# f = plt.figure(figsize=(5,4))
# canvas = FigureCanvasTkAgg(f, master= window)
# canvas.show()
def Bellman_Ford(no_of_nodes):
    MST = 0
    getfile = open(f"input{no_of_nodes}.txt")
    
    line = getfile.readline()
    line = getfile.readline()
    line = getfile.readline()
    nodes = int(line)#got nodes via type casting
    line = getfile.readline()
    xCoords = []#xCoordinates
    yCoords = []#yCoordsCoordinates
    
    for i in range(nodes):
        line = getfile.readline()
        fString = line.split()
        xCoords.append(float(fString[1]))
        yCoords.append(float(fString[2]))
        G.add_node(str(i), pos = (xCoords[i],yCoords[i]))
        G2.add_node(str(i), pos = (xCoords[i],yCoords[i]))
    
    

    adjMatrix = array([[inf] * nodes]*nodes)
    line = getfile.readline()
    for i in range(nodes):
        line = getfile.readline()
        fString = line.split()
        numberoffString = len(fString)
        fir = int(fString[0])
        for j in range(1,numberoffString,4):
            sec = int(fString[j])
            
            if(adjMatrix[fir,sec] > float(fString[j+2])/1000000):
                adjMatrix[fir,sec] = float(fString[j+2])/1000000
                adjMatrix[sec,fir] = adjMatrix[fir,sec]
            if( not (fir == sec)):
                G.add_edge(str(fir),str(sec))
            
    for i in range(nodes):
        adjMatrix[i,i] = 0
    for i in range(nodes):
        for j in range(nodes):
            print(str.format('{0:5}', adjMatrix[i,j]),end="  ")
        print()
    pos=nx.get_node_attributes(G,'pos')
    nx.draw(G,pos,with_labels = True)
    plt.show()
    
    line = getfile.readline()
    line = getfile.readline()
    distance =[inf] * nodes
    parent = [-1]*nodes
    
    l = int(line)
    distance[l] = 0
    
    for i in range(nodes-1):
        for edges in G.edges():
            d1 = distance[int(edges[0])] + adjMatrix[int(edges[0]),int(edges[1])]
            d2 = distance[int(edges[1])]
            if( d1 < d2):
                distance[int(edges[1])] = distance[int(edges[0])] + adjMatrix[int(edges[0]),int(edges[1])]
                parent[int(edges[1])] = int(edges[0])

            if(distance[int(edges[1])] + adjMatrix[int(edges[0]),int(edges[1])] < distance[int(edges[0])]):
                distance[int(edges[0])] = distance[int(edges[1])] + adjMatrix[int(edges[0]),int(edges[1])]
                parent[int(edges[0])] = int(edges[1])
    
    
    
    for e in G.edges():
        if(distance[int(e[0])] != inf and (distance[int(e[0])] + adjMatrix[int(e[0]),int(e[1])] < distance[int(e[1])])):
            print("Negative cyCoordscle detected!!!")
            exit(0)


    
    for i in range(nodes):
            
        j = i
        
        queue1 = []
        
        while(parent[j] != -1):
            
            G2.add_edge(str(parent[j]),str(j),)
            queue1.append(j)
            
            j = parent[j]

    nx.draw(G2,pos,with_labels = True)
    plt.show()
