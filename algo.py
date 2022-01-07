import turtle  #front(algos)
from turtle import Screen
from turtle import Turtle
import tkinter as tk  #front(main page)
from tkinter import Tk
from tkinter import ttk
from tkinter.filedialog import askopenfilename
from tkinter.filedialog import askopenfilename
from time import sleep
import itertools
import networkx as nx
import math

class Node:
    def __init__(self, x, y):
        self.x = x
        self.y = y

class Graph:
    def __init__(self,vertices): 
        self.V= vertices 
        self.graph = [] # default dictionary
        
    def union(self, parent, rank, x, y): 
        xroot = self.find(parent, x) 
        yroot = self.find(parent, y) 
        if rank[xroot] < rank[yroot]:  
            parent[xroot] = yroot 
        elif rank[xroot] > rank[yroot]: 
            parent[yroot] = xroot 
        else : 
            parent[yroot] = xroot #Make one as root and increment.
            rank[xroot] += 1

    
    # add an edge to the graph 

    def addEdge(self,u,v,w): 
        self.graph.append([u,v,w])
    
    def add_edge(self, u, v):
        self.graph.append([u, v])

    # find set of an element i 
    def find(self, parent, i): 
        if parent[i] == i: 
            return i 
        return self.find(parent, parent[i]) 

class File:
    def __init__(self):
        self.filename = ""
    def setFile(self, filename):
        self.filename = filename

class Algorithm:
    def setAlgo(self, algo):
        self.algo = algo

#define variables
algo = Algorithm()
algo.algo = ""
root = tk.Tk()
file = File()
nodes = []
matrix = []
num_nodes = 0
source_node = 0
INF = 9999999

def selectPrims():
    algo.setAlgo("Prims")
    setButtons("prims")

def selectKruskals():
     algo.setAlgo("Kruskals")
     setButtons("kruskals")

def selectFloyd():
     algo.setAlgo("Floyd-Warshall")
     setButtons("floyd")

def selectBellman():
     algo.setAlgo("Bellman-Ford")
     setButtons("bellman")

def selectDijikstra():
     algo.setAlgo("Dijikstra")
     setButtons("dijikstra")
    
def selectBoruvka():
    algo.setAlgo("Boruvka")
    setButtons("boruvka")

def selectCluster():
    algo.setAlgo("Local-Cluster")
    setButtons("local")

def makeMatrix(matrix, size):
    for x in range(size):
        row = []
        for y in range(size):
            row.append(0)
        matrix.append(row)


def rectifyValue(value):
    first_value = value.split(".")
    new_value = first_value[0][0]
    new_value += "."
    for x in range(1, len(first_value[0])):
        new_value += first_value[0][x]

    return float(new_value)


def getFile():
    Tk().withdraw() 
    file.setFile(askopenfilename())
    root.quit()


def readFile():
    global num_nodes, source_node, file
    file = open(file.filename, "r")
    lines = file.readlines()
    num_nodes = int(lines[2])
    source_node = int(lines[len(lines)-1])
    print(num_nodes)
    makeMatrix(matrix, num_nodes)

    for x in range(4, 4+num_nodes):
        node_info = lines[x].split('\t')
        node = Node(float(node_info[1]) * 500 - 300, float(node_info[2]) * 500 - 150)
        nodes.append(node)


    row = 0
    for x in range(5+num_nodes, 6+num_nodes + num_nodes-1):
        line = lines[x].split('\t')
        neighbours = int(line[0])
        pos = 1
        for y in range(neighbours):
            col = int(line[pos])
            value = rectifyValue(line[pos+2])
            matrix[row][col] = value
            pos = pos + 4
        row = row + 1

# def removeOverlap(nodes, new_node, node_num):
#     for x in range(node_num):

def setButtons(algo=""):
    prims = tk.Button(
    root,
    text='Prims',
    font="bold",
    command=lambda: selectPrims(),
    bg="#a60505" if algo == "prims" else "#E9072B",
    fg="white",
    height = 2,
    width = 13
    )

    prims.place(x = 50, y = 150)

    kruskals = tk.Button(
    root,
    text='Kruskals',
    font="bold",
    command=lambda: selectKruskals(),
    bg="#a60505" if algo == "kruskals" else "#E9072B",
    fg="white",
    height = 2,
    width = 13
    )
    kruskals.place(x = 180, y = 150)

    dijikstra = tk.Button(
    root,
    text='Dijikstra',
    font="bold",
    command=lambda: selectDijikstra(),
    bg="#a60505" if algo == "dijikstra" else "#E9072B",
    fg="white",
    height = 2,
    width = 13
    )

    dijikstra.place(x= 50, y= 200)

    floyd = tk.Button(
    root,
    text='Floyd Warshall',
    font="bold",
    command=lambda: selectFloyd(),
    bg="#a60505" if algo == "floyd" else "#E9072B",
    fg="white",
    height = 2,
    width = 13
    )

    floyd.place(x=180, y=200)

    bellman = tk.Button(
    root,
    text='Bellman Ford',
    font="bold",
    command=lambda: selectBellman(),
    bg="#a60505" if algo == "bellman" else "#E9072B",
    fg="white",
    height = 2,
    width = 13
    )

    bellman.place(x=50, y=250)

    boruvka = tk.Button(
    root,
    text='Boruvka',
    font="bold",
    command=lambda: selectBoruvka(),
    bg="#a60505" if algo == "boruvka" else "#E9072B",
    fg="white",
    height = 2,
    width = 13
    )

    boruvka.place(x=180, y=250)

    cluster = tk.Button(
    root,
    text='Cluster Coefficient',
    font="bold",
    command=lambda: selectCluster(),
    bg="#a60505" if algo == "local" else "#E9072B",
    fg="white",
    height = 2,
    width = 15
    )

    cluster.place(x=110, y=300)

def mainScreen():
    root.geometry('700x600+320+100')
    root['background']='#001628'
    root.resizable(False, False)
    root.title('Algo Project')
    select_algo = tk.Label(text="Select an Algorithm", font=("Helvetica", 20, "bold"), bg="#001628", fg="white")
    select_algo.place(x = 50, y = 60)
    select_inputfile = tk.Label(text="Select an Input file", font=("Helvetica", 20, "bold"), bg="#001628", fg="white")
    select_inputfile.place(x = 360, y = 60)
    select_file = tk.Button(
    root,
    text='Click to select input file',
    font="bold",
    command=lambda: getFile(),
    bg="#E9072B",
    fg="white",
    height = 5,
    width = 20
    )

    select_file.place(x=400, y=150)
    setButtons()
    root.mainloop()
    cv = turtle.ScrolledCanvas(root, width=1000, height=1000)
    cv.pack()
    return cv
    # root.destroy()

def prims_algorithm(line_turtle, write_turtle):
    line_turtle.hideturtle()
    line_turtle.reset()
    line_turtle.color((104, 162, 185))
    write_turtle.reset()
    write_turtle.color((104, 162, 185))
    style = ('Arial', 20, 'bold')
    write_turtle.hideturtle()
    write_turtle.penup()
    write_turtle.goto(-150, 240)
    write_turtle.write(algo.algo + " Algorithm", font=style)
# number of vertices in graph
    N = num_nodes
# creating graph by adjacency matrix method
    G = matrix

    selected_node = []
    for x in range(num_nodes):
        selected_node.append(0)

    no_edge = 0

    selected_node[source_node] = True
    node_turtles[source_node].fillcolor((98, 3, 0))
    label_turtle.color('white')
    label_turtle.speed('fastest')
    style = ('Arial', 10, 'bold')
    label_turtle.hideturtle()
    label_turtle.penup()
    label_turtle.goto(nodes[source_node].x-2, nodes[source_node].y-7)
    label_turtle.write(str(source_node), font=style)

# printing for edge and weight
    print("Edge : Weight\n")
    mst = 0
    while (no_edge < N - 1):

        minimum = INF
        a = 0
        b = 0
        for m in range(N):
            if selected_node[m]:
                for n in range(N):
                    if ((not selected_node[n]) and G[m][n]):
                    # not in selected and there is an edge
                        if minimum > G[m][n]:
                            minimum = G[m][n]
                            a = m
                            b = n
        x = (nodes[a].x, nodes[a].y)
        y = (nodes[b].x, nodes[b].y)
        line_turtle.hideturtle()
        line_turtle.penup()
        line_turtle.goto(x)
        line_turtle.showturtle()
        line_turtle.pendown()
        line_turtle.goto(y)
        # print(str(a) + "-" + str(b) + ":" + str(G[a][b]))
        mst += G[a][b]
        selected_node[b] = True
        node_turtles[b].fillcolor((233, 7, 43))
        label_turtle.color('white')
        style = ('Arial', 10, 'bold')
        label_turtle.hideturtle()
        label_turtle.penup()
        label_turtle.goto(nodes[b].x-2, nodes[b].y-7)
        label_turtle.write(str(b), font=style)
        no_edge += 1

    write_text.color(104, 162, 185)
    style = ('Arial', 15, 'bold')
    write_text.hideturtle()
    write_text.penup()
    write_text.goto(-250, -220)
    write_text.write("MST Cost: " + str(mst), font=style)

def changeMatrix():
    for x in range(num_nodes):
        for y in range(num_nodes):
            if matrix[x][y] == 0:
                matrix[x][y] = INF

def find(i, parent):
    while parent[i] != i:
        i = parent[i]
    return i

def union(i, j, parent):
    a = find(i, parent)
    b = find(j, parent)
    parent[a] = b 

def kruskals_algorithm(line_turtle, write_turtle):
    line_turtle.hideturtle()
    write_turtle.reset()
    write_turtle.color(((104, 162, 185)))
    line_turtle.reset()
    line_turtle.color((104, 162, 185))
    style = ('Arial', 20, 'bold')
    write_turtle.hideturtle()
    write_turtle.penup()
    write_turtle.goto(-150, 240)
    write_turtle.write(algo.algo + " Algorithm", font=style)
    changeMatrix()
    V = num_nodes
    parent = [i for i in range(V)]
    mincost = 0 # Cost of min MST
 
    # Initialize sets of disjoint sets
    for i in range(V):
        parent[i] = i
 
    # Include minimum weight edges one by one
    edge_count = 0
    while edge_count < V - 1:
        min = INF
        a = -1
        b = -1
        for i in range(V):
            for j in range(V):
                if find(i, parent) != find(j, parent) and matrix[i][j] < min:
                    min = matrix[i][j]
                    a = i
                    b = j

        
        x = (nodes[a].x, nodes[a].y)
        y = (nodes[b].x, nodes[b].y)
        line_turtle.speed('fastest')
        node_turtles[a].fillcolor((233, 7, 43))
        label_turtle.speed('fastest')
        label_turtle.color('white')
        style = ('Arial', 10, 'bold')
        label_turtle.hideturtle()
        label_turtle.penup()
        label_turtle.goto(nodes[a].x-2, nodes[a].y-7)
        label_turtle.write(str(a), font=style)
        node_turtles[b].fillcolor((233, 7, 43))
        label_turtle.speed('fastest')
        label_turtle.color('white')
        style = ('Arial', 10, 'bold')
        label_turtle.hideturtle()
        label_turtle.penup()
        label_turtle.goto(nodes[b].x-2, nodes[b].y-7)
        label_turtle.write(str(b), font=style)
        line_turtle.hideturtle()
        line_turtle.penup()
        line_turtle.goto(x)
        line_turtle.showturtle()
        line_turtle.pendown()
        line_turtle.goto(y)
        union(a, b, parent)
        print('Edge {}:({}, {}) cost:{}'.format(edge_count, a, b, min))
        edge_count += 1
        mincost += min
 
    print("Minimum cost= {}".format(mincost))
    write_text.color(104, 162, 185)
    style = ('Arial', 15, 'bold')
    write_text.hideturtle()
    write_text.penup()
    write_text.goto(-250, -220)
    write_text.write("MST Cost: " + str(mincost), font=style)


def minDistance(dist,queue):
        # Initialize min value and min_index as -1
        minimum = INF
        min_index = -1
         
        # from the dist array,pick one which
        # has min value and is till in queue
        for i in range(len(dist)):
            if dist[i] < minimum and i in queue:
                minimum = dist[i]
                min_index = i
        return min_index

def dijikstra_algorithm(line_turtle, write_turtle):
    line_turtle.hideturtle()
    write_turtle.reset()
    write_turtle.color(((104, 162, 185)))
    line_turtle.reset()
    line_turtle.color((104, 162, 185))
    style = ('Arial', 20, 'bold')
    write_turtle.hideturtle()
    write_turtle.penup()
    write_turtle.goto(-150, 240)
    write_turtle.write(algo.algo + " Algorithm", font=style)
    row = num_nodes
    col = num_nodes
 
        # The output array. dist[i] will hold
        # the shortest distance from src to i
        # Initialize all distances as INFINITE
    dist = [INF] * row

        #Parent array to store
        # shortest path tree
    parent = [-1] * row
 
        # Distance of source vertex
        # from itself is always 0
    dist[source_node] = 0
     
        # Add all vertices in queue
    queue = []
    for i in range(row):
        queue.append(i)
             
        #Find shortest path for all vertices
    while queue:
 
            # Pick the minimum dist vertex
            # from the set of vertices
            # still in queue
        u = minDistance(dist,queue)
        node_turtles[u].fillcolor((233, 7, 43))
        label_turtle.color('white')
        style = ('Arial', 10, 'bold')
        label_turtle.hideturtle()
        label_turtle.penup()
        label_turtle.goto(nodes[u].x-2, nodes[u].y-7)
        label_turtle.write(str(u), font=style)
        node_turtles[source_node].fillcolor((98, 3, 0))
        label_turtle.color('white')
        style = ('Arial', 10, 'bold')
        label_turtle.hideturtle()
        label_turtle.penup()
        label_turtle.goto(nodes[source_node].x-2, nodes[source_node].y-7)
        label_turtle.write(str(source_node), font=style)
            # remove min element    
        queue.remove(u)
 
            # Update dist value and parent
            # index of the adjacent vertices of
            # the picked vertex. Consider only
            # those vertices which are still in
            # queue
        for i in range(col):
            if matrix[u][i] and i in queue:
                if dist[u] + matrix[u][i] < dist[i]:
                    dist[i] = dist[u] + matrix[u][i]
                    if dist[i] != 0:
                        if parent[i] != -1:
                            u_ = parent[i]
                            x = (nodes[u_].x, nodes[u_].y)
                            y = (nodes[i].x, nodes[i].y)
                            line_turtle.speed('fastest')
                            line_turtle.color((0, 22, 40))
                            line_turtle.hideturtle()
                            line_turtle.penup()
                            line_turtle.goto(x)
                            line_turtle.showturtle()
                            line_turtle.pendown()
                            line_turtle.goto(y)
                    parent[i] = u
                    x = (nodes[u].x, nodes[u].y)
                    y = (nodes[i].x, nodes[i].y)
                    line_turtle.speed('fastest')
                    node_turtles[u].fillcolor((233, 7, 43))
                    label_turtle.color('white')
                    style = ('Arial', 10, 'bold')
                    label_turtle.speed('fastest')
                    label_turtle.hideturtle()
                    label_turtle.penup()
                    label_turtle.goto(nodes[u].x-2, nodes[u].y-7)
                    label_turtle.write(str(u), font=style)
                    node_turtles[i].fillcolor((233, 7, 43))
                    label_turtle.speed('fastest')
                    label_turtle.color('white')
                    style = ('Arial', 10, 'bold')
                    label_turtle.hideturtle()
                    label_turtle.penup()
                    label_turtle.goto(nodes[i].x-2, nodes[i].y-7)
                    label_turtle.write(str(i), font=style)
                    line_turtle.hideturtle()
                    line_turtle.color(104, 162, 185)
                    line_turtle.penup()
                    line_turtle.goto(x)
                    line_turtle.showturtle()
                    line_turtle.pendown()
                    line_turtle.goto(y)

    write_text.color(104, 162, 185)
    style = ('Arial', 15, 'bold')
    write_text.hideturtle()
    write_text.penup()
    write_text.goto(-250, -220)
    write_text.write("Results", font=style)
    for i in range(col):
        style = ('Arial', 10, 'bold')
        write_text.hideturtle()
        write_text.penup()
        write_text.goto(-250, -220 - 20*(i+1))
        write_text.write("Vertex " + str(i) + "-> cost = " + str(round(dist[i], 3)) + " parent = " + str(parent[i]), font=style)

def bellman_ford(line_turtle, write_turtle):
    write_turtle.reset()
    write_turtle.color(((104, 162, 185)))
    line_turtle.reset()
    line_turtle.color((104, 162, 185))
    style = ('Arial', 20, 'bold')
    write_turtle.hideturtle()
    write_turtle.penup()
    write_turtle.goto(-150, 240)
    write_turtle.write(algo.algo + " Algorithm", font=style)
    V = num_nodes
    edge = []
    for x in range(V*V):
        hold = []
        for y in range(2):
            hold.append(0)
        edge.append(hold)

    k = 0

    for x in range(V):
        for y in range(V):
            if matrix[x][y] != 0:
                edge[k][0]=x
                k += 1
                edge[k][1]=y
    
    u = 0
    v = 0
    E = k
    k = 0
    distance = []
    parent = []
    S = source_node
    flag = True
    for i in range(V):
        distance.append(1000)
        parent.append(-1)
    
    distance[S]=0
    
    for i in range(V):
        for k in range(E):
            u = edge[k][0]
            v = edge[k][1]
            if distance[u] + matrix[u][v] < distance[v]:
                distance[v] = distance[u] + matrix[u][v]
                if parent[v] != -1:
                    u_ = parent[v]
                    x = (nodes[u_].x, nodes[u_].y)
                    y = (nodes[v].x, nodes[v].y)
                    line_turtle.speed('fastest')
                    line_turtle.color(0, 22, 40)
                    line_turtle.hideturtle()
                    line_turtle.penup()
                    line_turtle.goto(x)
                    line_turtle.showturtle()
                    line_turtle.pendown()
                    line_turtle.goto(y)
                parent[v] = u
                x = (nodes[u].x, nodes[u].y)
                y = (nodes[v].x, nodes[v].y)
                line_turtle.speed('fastest')
                if u == S:
                    node_turtles[u].fillcolor((98, 3, 0))
                else: 
                    node_turtles[u].fillcolor((233, 7, 43))
                label_turtle.speed('fastest')
                label_turtle.color('white')
                style = ('Arial', 10, 'bold')
                label_turtle.hideturtle()
                label_turtle.penup()
                label_turtle.goto(nodes[u].x-2, nodes[u].y-7)
                label_turtle.write(str(u), font=style)
                if v == S:
                    node_turtles[v].fillcolor((98, 3, 0))
                else: 
                    node_turtles[v].fillcolor((233, 7, 43))
                label_turtle.speed('fastest')
                label_turtle.color('white')
                style = ('Arial', 10, 'bold')
                label_turtle.hideturtle()
                label_turtle.penup()
                label_turtle.goto(nodes[v].x-2, nodes[v].y-7)
                label_turtle.write(str(v), font=style)
                line_turtle.color(104, 162, 185)
                line_turtle.hideturtle()
                line_turtle.penup()
                line_turtle.goto(x)
                line_turtle.showturtle()
                line_turtle.pendown()
                line_turtle.goto(y)

    style = ('Arial', 15, 'bold')
    write_turtle.hideturtle()
    write_turtle.penup()
    write_turtle.goto(-250, -220)
    write_turtle.write("Results on Console", font=style) 
    for k in range(E):
        u = edge[k][0]
        v = edge[k][1]
        if distance[u] + matrix[u][v] < distance[v]:
            flag = False
        if flag:
            for i in range(V):
                style = ('Arial', 10, 'bold')
                write_text.hideturtle()
                write_text.penup()
                write_text.goto(-250, -220 - 20*(i+1))
                write_text.write("Vertex " + str(i) + "-> cost = " + str(round(distance[i], 3)) + " parent = " + str(parent[i]), font=style)

        return flag

def floyd_warshall(line_turtle, write_turtle):
    write_turtle.reset()
    write_turtle.color(((104, 162, 185)))
    style = ('Arial', 20, 'bold')
    write_turtle.hideturtle()
    write_turtle.penup()
    write_turtle.goto(-150, 240)
    write_turtle.write(algo.algo + " Algorithm", font=style)
    line_turtle.reset()
    line_turtle.color((104, 162, 185))
    changeMatrix()
    dist = list(map(lambda i: list(map(lambda j: j, i)), matrix))
    V = num_nodes
    parent = []
    for x in range(V):
        parent.append(-1)
    for k in range(V):
        for i in range(V):
            for j in range(V):
                hold = dist[i][j]
                if (dist[i][k] + dist[k][j] < dist[i][j]):
                    dist[i][j] = dist[i][k] + dist[k][j]
                    parent[j] = k
                    x = (nodes[i].x, nodes[i].y)
                    y = (nodes[j].x, nodes[j].y)
                    line_turtle.speed('fastest')
                    line_turtle.color(0, 22, 40)
                    node_turtles[i].fillcolor((233, 7, 43))
                    label_turtle.speed('fastest')
                    label_turtle.color('white')
                    style = ('Arial', 10, 'bold')
                    label_turtle.hideturtle()
                    label_turtle.penup()
                    label_turtle.goto(nodes[i].x-2, nodes[i].y-7)
                    label_turtle.write(str(i), font=style)
                    node_turtles[j].fillcolor((233, 7, 43))
                    label_turtle.speed('fastest')
                    label_turtle.color('white')
                    style = ('Arial', 10, 'bold')
                    label_turtle.hideturtle()
                    label_turtle.penup()
                    label_turtle.goto(nodes[j].x-2, nodes[j].y-7)
                    label_turtle.write(str(j), font=style)
                    line_turtle.hideturtle()
                    line_turtle.penup()
                    line_turtle.goto(x)
                    line_turtle.showturtle()
                    line_turtle.pendown()
                    line_turtle.goto(y)
                    x = (nodes[i].x, nodes[i].y)
                    y = (nodes[k].x, nodes[k].y)
                    if matrix[i][k] != INF:
                        line_turtle.speed('fastest')
                        node_turtles[i].fillcolor((233, 7, 43))
                        node_turtles[k].fillcolor((233, 7, 43))
                        line_turtle.hideturtle()
                        line_turtle.penup()
                        line_turtle.goto(x)
                        line_turtle.showturtle()
                        line_turtle.pendown()
                        line_turtle.goto(y)
                    x = (nodes[k].x, nodes[k].y)
                    y = (nodes[j].x, nodes[j].y)
                    if matrix[k][j] != INF:
                        line_turtle.speed('fastest')
                        node_turtles[k].fillcolor((233, 7, 43))
                        node_turtles[j].fillcolor((233, 7, 43))
                        line_turtle.color(104, 162, 185)
                        line_turtle.hideturtle()
                        line_turtle.penup()
                        line_turtle.goto(x)
                        line_turtle.showturtle()
                        line_turtle.pendown()
                        line_turtle.goto(y)

    print(dist)
    style = ('Arial', 15, 'bold')
    write_text.hideturtle()
    write_text.penup()
    write_text.goto(-250, -220)
    write_text.write("Results:", font=style)

    for i in range(V):
        style = ('Arial', 12, 'bold')
        write_text.hideturtle()
        write_text.penup()
        write_text.goto(-230 + i*30, - 250)
        write_text.write(str(i), font=style)
        write_text.goto(-250, -265 - i*20)
        write_text.write(str(i), font=style)
    for i in range(V):
        for j in range(V):
            style = ('Arial', 10, 'bold')
            write_text.hideturtle()
            write_text.penup()
            write_text.goto(-230 + j*30, -265 - i*20)
            distance = 0 if i == j else round(dist[i][j], 1)
            write_text.write(str(distance), font=style)


def makeGraph(graph):
    for x in range(graph.V):
        for y in range(graph.V):
            if matrix[x][y] != 0:
                graph.addEdge(x, y, matrix[x][y])
 

def makeGraph_(graph):
    for x in range(graph.V):
        for y in range(graph.V):
            if matrix[x][y] != 0:
                graph.add_edge(x, y)

def boruvka_algorithm(line_turtle, write_turtle):
    write_turtle.reset()
    write_turtle.color(((104, 162, 185)))
    style = ('Arial', 20, 'bold')
    write_turtle.hideturtle()
    write_turtle.penup()
    write_turtle.goto(-150, 240)
    write_turtle.write(algo.algo + " Algorithm", font=style)
    line_turtle.reset()
    line_turtle.color((104, 162, 185))
    G = Graph(num_nodes)
    makeGraph(G)
    parent = []
    rank = []
    cheapest =[]      
    numTrees = G.V 
    MSTweight = 0     
    for node in range(G.V): 
        parent.append(node) 
        rank.append(0) 
        cheapest =[-1] * G.V 
        # Keep combining components (or sets) until all 
        # compnentes are not combined into single MST 
    while numTrees > 1: 
        for i in range(len(G.graph)): 
            u,v,w = G.graph[i] 
            set1 = G.find(parent, u) 
            set2 = G.find(parent ,v)
            if set1 != set2:   
                if cheapest[set1] == -1 or cheapest[set1][2] > w : 
                    cheapest[set1] = [u,v,w] 
                if cheapest[set2] == -1 or cheapest[set2][2] > w : 
                    cheapest[set2] = [u,v,w] 

            # Consider the above picked cheapest edges and add them to MST 
        for node in range(G.V): 
            if cheapest[node] != -1: 
                u,v,w = cheapest[node] 
                set1 = G.find(parent, u) 
                set2 = G.find(parent ,v) 
                if set1 != set2 : 
                    MSTweight += w 
                    x = (nodes[u].x, nodes[u].y)
                    y = (nodes[v].x, nodes[v].y)
                    line_turtle.speed('fastest')
                    node_turtles[u].fillcolor((233, 7, 43))
                    label_turtle.speed('fastest')
                    label_turtle.color('white')
                    style = ('Arial', 10, 'bold')
                    label_turtle.hideturtle()
                    label_turtle.penup()
                    label_turtle.goto(nodes[u].x-2, nodes[u].y-7)
                    label_turtle.write(str(u), font=style)
                    node_turtles[v].fillcolor((233, 7, 43))
                    label_turtle.speed('fastest')
                    label_turtle.color('white')
                    style = ('Arial', 10, 'bold')
                    label_turtle.hideturtle()
                    label_turtle.penup()
                    label_turtle.goto(nodes[v].x-2, nodes[v].y-7)
                    label_turtle.write(str(v), font=style)
                    line_turtle.hideturtle()
                    line_turtle.penup()
                    line_turtle.goto(x)
                    line_turtle.showturtle()
                    line_turtle.pendown()
                    line_turtle.goto(y)
                    G.union(parent, rank, set1, set2) 
                    print ("Edge %d-%d has weight %d is included in MST" % (u,v,w)) 
                    numTrees = numTrees - 1
         
        cheapest =[-1] * G.V 
    print ("Weight of MST is %.2f" % MSTweight) 
    style = ('Arial', 15, 'bold')
    write_text.hideturtle()
    write_text.penup()
    write_text.goto(-250, -220)
    write_text.write("MST Cost: " + str(MSTweight), font=style)


def local_clustering(line_turtle, write_turtle):
    graph = Graph(num_nodes)
    makeGraph_(graph)
    G = nx.Graph()
 
    G.add_edges_from(graph.graph)
 
# returns a Dictionary with clustering value of each node
    
    write_turtle.reset()
    write_turtle.color(((104, 162, 185)))
    style = ('Arial', 20, 'bold')
    write_turtle.hideturtle()
    write_turtle.penup()
    write_turtle.goto(-150, 240)
    write_turtle.write(algo.algo + " Algorithm", font=style)
    sum_ = []
    V = num_nodes
    for i in range(V):
        node_turtles[i].fillcolor((233, 7, 43))
        label_turtle.speed('fastest')
        label_turtle.color('white')
        style = ('Arial', 10, 'bold')
        label_turtle.hideturtle()
        label_turtle.penup()
        label_turtle.goto(nodes[i].x-2, nodes[i].y-7)
        label_turtle.write(str(i), font=style)
        sleep(0.5)
        for j in range(V):
            if matrix[i][j]:
                node_turtles[j].fillcolor((233, 7, 43))
                label_turtle.speed('fastest')
                label_turtle.color('white')
                style = ('Arial', 10, 'bold')
                label_turtle.hideturtle()
                label_turtle.penup()
                label_turtle.goto(nodes[j].x-2, nodes[j].y-7)
                label_turtle.write(str(j), font=style)
        sleep(0.5)
        s=[b for b in range(V) if matrix[i][b]]
        k=len(s)
        if k<2:
            #cannot make local clustering
            return 0
        value = 2.0*sum(map(lambda x:matrix[x[0]][x[1]],itertools.combinations(s,2)))/k/(k-1)
        sum_.append(value)
        node_turtles[i].fillcolor((230, 70, 124))
        label_turtle.speed('fastest')
        label_turtle.color('white')
        style = ('Arial', 10, 'bold')
        label_turtle.hideturtle()
        label_turtle.penup()
        label_turtle.goto(nodes[i].x-2, nodes[i].y-7)
        label_turtle.write(str(i), font=style)
        for j in range(V):
            if matrix[i][j]:
                node_turtles[j].fillcolor((230, 70, 124))
                label_turtle.speed('fastest')
                label_turtle.color('white')
                style = ('Arial', 10, 'bold')
                label_turtle.hideturtle()
                label_turtle.penup()
                label_turtle.goto(nodes[j].x-2, nodes[j].y-7)
                label_turtle.write(str(j), font=style)
    # print(sum(sum_)/V)
    res = nx.average_clustering(G)
    print(res)
    style = ('Arial', 15, 'bold')
    write_text.hideturtle()
    write_text.penup()
    write_text.goto(-250, -220)
    write_text.write("Average Local Clustering Coefficient: " + str(round(res, 3)), font=style)
    for i in range(V):
        style = ('Arial', 10, 'bold')
        write_text.hideturtle()
        write_text.penup()
        write_text.goto(-250, -220 - 20*(i+1))
        write_text.write("Clustering Coefficient for Vertex# " + str(i) + ": " + str(round(nx.clustering(G, i), 3)), font=style)


# driver code

cv = mainScreen()
readFile()

screen = turtle.TurtleScreen(cv)
screen.screensize(700,600 + 50*num_nodes) #added by me
screen.colormode(255)
screen.bgcolor(0, 22, 40)
write_text = turtle.RawTurtle(screen)
label_turtle = turtle.RawTurtle(screen)
style = ('Arial', 20, 'bold')
write_text.hideturtle()
write_text.penup()
write_text.goto(-100, 240)
write_text.color((104, 162, 185))
write_text.write('Original Graph', font=style)

node_turtles = [] #nodes
for x in range(num_nodes):
    node_turtle = turtle.RawTurtle(screen)
    node_turtle.hideturtle()
    node_turtle.penup()
    node_turtle.fillcolor((230, 70, 124))
    node_turtle.shape('circle')
    node_turtle.speed('fastest')
    node_turtle.goto(nodes[x].x, nodes[x].y)
    node_turtle.showturtle()
    node_turtle.pendown()
    node_turtles.append(node_turtle)
    label_turtle.speed('fastest')
    label_turtle.color('white')
    style = ('Arial', 10, 'bold')
    label_turtle.hideturtle()
    label_turtle.penup()
    label_turtle.goto(nodes[x].x-2, nodes[x].y-7)
    label_turtle.write(str(x), font=style)


line_turtle = turtle.RawTurtle(screen)  #edges
line_turtle.speed('fastest')
arrow_turtles = []
# make graph
for x_ in range(num_nodes):
    for y_ in range(num_nodes):
        if matrix[x_][y_] != 0:
            # arrow_turtle = turtle.RawTurtle(screen)
            x = (nodes[x_].x, nodes[x_].y)
            y = (nodes[y_].x, nodes[y_].y)
            line_turtle.hideturtle()
            line_turtle.pencolor((104, 162, 185))
            line_turtle.penup()
            line_turtle.goto(x)
            line_turtle.showturtle()
            line_turtle.pendown()
            line_turtle.goto(y)
            # arrow_turtle.color("black")
            # arrow_turtle.penup()
            # arrow_turtle.goto(x)
            # angle = 0
            # if x[0] - y[0] == 0:
            #     if (x[1] - y[1])*(x[0] - y[0]) < 0:
            #         angle = -90
            #     else:
            #         angle = 90
            # else:
            #     m = (x[1] - y[1])/(x[0] - y[0])
            #     angle = math.atan(m) * (180 / math.pi)
            # print(angle)
            # arrow_turtle.setheading(angle)
            # arrow_turtle.forward(math.dist(x, y) - 10)

sleep(2)

if algo.algo == "Prims":
    prims_algorithm(line_turtle, write_text)
elif algo.algo == "Kruskals":
    kruskals_algorithm(line_turtle, write_text)
elif algo.algo == "Dijikstra": 
    dijikstra_algorithm(line_turtle, write_text)
elif algo.algo == "Bellman-Ford":
    bellman_ford(line_turtle, write_text)
elif algo.algo == "Floyd-Warshall":
    floyd_warshall(line_turtle, write_text)
elif algo.algo == "Boruvka":
    boruvka_algorithm(line_turtle, write_text)
elif algo.algo == "Local-Cluster":
    local_clustering(line_turtle, write_text)

root.mainloop()