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

G = nx.Graph()
G2 = nx.Graph()
entered = 0
def Prims(no_of_nodes):
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
    
    
    is_taken = [0]*nodes
    edges = 0
    line = getFile.readline()
    line = getFile.readline()
    is_taken[int(line)] = True
    
    while(edges < nodes-1):
        min = inf
        a = 0
        b = 0
        for i  in range(nodes):
            if(is_taken[i]):
                for j in range(nodes):
                        if((not is_taken[j]) and adjMatrix[i,j]):
                            if(min > adjMatrix[i,j]):
                                a = i
                                b = j
                                min = adjMatrix[i,j]
        MST+=adjMatrix[a,b]
        G2.add_edge(str(a),str(b))
        
        is_taken[b] = True
        edges+=1
    print("MST: " + str(MST))
    nx.draw(G2,pos,with_labels = True)
    plt.show()
    # return [G, G2]
#  canvas.draw()
#  window.mainloop()

# VertexData = Entry(window)

# VertexData.grid(row = 0, column = 0)
# Button(window, text = "Insert Vertex").grid(sticky = W, row = 0, column = 1, padx = 4)
# Button(window, text = "Delete Vertex").grid(sticky = W, row = 0, column = 2, padx = 4)
# Button(window, text = "MaxFlow").grid(sticky = W, row = 0, column = 3, padx = 4, command = Prims(10))
# df3 = DataFrame()





# f = plt.Figure(figsize=(5, 5), dpi=100)
# canvas = FigureCanvasTkAgg(f, window)

# # get canvas as tkinter's widget and `gird` in widget `window`
# canvas.get_tk_widget().grid(row=..., column=...)