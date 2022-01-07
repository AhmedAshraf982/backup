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
# canvas.show()s

def find(i,parent):
    while parent[i] != i:
        i = parent[i]
    return i
def union(i, j,parent): # for kruskal
    a = find(i,parent)
    b = find(j,parent)
    parent[a] = b

def krus(adjMat,nodes,parent):
    mst = 0
    for i in range(nodes):
        parent[i] = i
    edges = 0
    while edges < nodes - 1:
        min = inf
        a = -1
        b = -1
        for i in range(nodes):
            for j in range(nodes):
                findResult = find(i,parent) != find(j,parent)
                if adjMat[i][j] < min and findResult:
                    min = adjMat[i][j]
                    a = i
                    b = j
        union(a, b,parent)
        
        edges += 1
        mst += min
        G2.add_edge(str(a),str(b))
    
    return mst
def Kruskals(no_of_nodes):
 #entered = entered*10
 #filename = "input" + str(entered) + ".txt"
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

    parent = [i for i in range(nodes)]
    MST = krus(adjMatrix,nodes,parent)
    
    print("MST: " + str(MST))
    
    nx.draw(G2,pos,with_labels = True)
    plt.show()