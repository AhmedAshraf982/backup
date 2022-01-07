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
def combine(e,setMatrix):
	e0 = -1
	e1 = -1
	for i in range(0,len(setMatrix)):
		if e[0] in setMatrix[i]:
			e0 = i
		if e[1] in setMatrix[i]:
			e1 = i
	setMatrix[e0] += setMatrix[e1]
	del setMatrix[e1]

def Boruvka(no_of_nodes):
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
    for i in range(nodes):
        for j in range(nodes):
            print(str.format('{0:5}', adjMatrix[i,j]),end="  ")
        print()
    pos=nx.get_node_attributes(G,'pos')
    nx.draw(G,pos,with_labels = True)
    plt.show()
    setMatrix = []
    for i in range(0,len(adjMatrix)):
            setMatrix.append([i])
    print("Initial Grouping: " + str(setMatrix))
    while (len(setMatrix) > 1):
        edges = []
        for component in setMatrix:
            m = [999,[0,0]]
            for vertex in component:
                for i in range(0,len(adjMatrix[0])):
                        if i not in component and adjMatrix[vertex][i] != 0:
                            if (m[0] > adjMatrix[vertex][i]):
                                m[0] = adjMatrix[vertex][i]
                                m[1] = [vertex,i]
            if (m[1][0] > m[1][1]):
                m[1][0], m[1][1] =  m[1][1],m[1][0]
            if (m[1] not in edges):
                edges.append(m[1])
        for e in edges:
            combine(e,setMatrix)
        print("Edges formed: " + str(edges) + " Groupings: " + str(setMatrix))
        for e in edges:
            a = str(e[0])
            b = str(e[1])
            MST+= adjMatrix[int(a)][int(b)]
            G2.add_edge(a,b)
    
    print("MST = ",MST)

    nx.draw(G2,pos,with_labels = True)
    plt.show()