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
def Dijsktra(no_of_nodes):
    MST = 0
    getFile = open(f"input{no_of_nodes}.txt")
    
    line = getFile.readline()
    line = getFile.readline()
    line = getFile.readline()
    nodes = int(line)#got nodes via type casting
    line = getFile.readline()
    xCoords = []#xCoordinates
    yCoords = []#yCoordsCoordinates
    
    for i in range(nodes):
        line = getFile.readline()
        fString = line.split()
        
        xCoords.append(float(fString[1]))
        yCoords.append(float(fString[2]))

        G.add_node(str(i), pos = (xCoords[i],yCoords[i]))
        G2.add_node(str(i), pos = (xCoords[i],yCoords[i]))


    adjMatrix = array([[inf]* nodes]*nodes)
    line = getFile.readline()
    for i in range(nodes):
        line = getFile.readline()
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
    
    pos=nx.get_node_attributes(G,'pos')
    nx.draw(G,pos,with_labels = True)
    plt.show()
    dist = [inf] * nodes
    parent = [-1] * nodes
    line = getFile.readline()
    line = getFile.readline()
    dist[int(line)] = 0
    queue = []
    for i in range (nodes):
        queue.append(i)
    while (queue):
        minimum = inf
        min_index = -1
        for i in range (nodes):
            if (dist[i] < minimum and i in queue):
                minimum = dist[i]
                min_index = i
        queue.remove(min_index)
        for i in range (nodes):
            if (adjMatrix[min_index][i] and i in queue):
                if (dist[min_index] + adjMatrix[min_index,i] < dist[i]):
                        dist[i] = dist[min_index] + adjMatrix[min_index,i]
                        parent[i] = min_index
                        G2.add_edge(str(min_index),str(i))
    
    for i in range(nodes):
        j = i
        queue1 = []
        while(parent[j] != -1):
            G2.add_edge(str(parent[j]),str(j))
            queue1.append(j)
            j = parent[j]
            
    nx.draw(G2,pos,with_labels = True)
    plt.show()
    #  return MST