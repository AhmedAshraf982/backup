from networkx.classes.function import number_of_nodes
from numpy import number
import kruskal
import prims
import dijkstra
import bellman_ford
import floyd
import cluster
import boruvka
from tkinter import *

ALGORITHMS = [
    "Bellman Ford's Algorithm",
    "Prims' Algorithm",
    "Kruskal's Algorithm",
    "Cluster Algorithm",
    "Dijkstra's Algorithm",
    "Floyd Warshall's Algorithm",
    "Boruvka's Algorithm"
]

def compute():
    global numberOfNodes, algorithm
    nodesChosen = numberOfNodes.get()[0:2]
    algorithmChosen = algorithm.get()
    print("IN COMPUTE\n"+ str(nodesChosen) + ' ' + algorithmChosen)
    if(algorithmChosen == ALGORITHMS[0]):
        bellman_ford.Bellman_Ford(nodesChosen)
    elif(algorithmChosen == ALGORITHMS[1]):
        prims.Prims(nodesChosen)
    elif(algorithmChosen == ALGORITHMS[2]):
        kruskal.Kruskals(nodesChosen)
    elif(algorithmChosen == ALGORITHMS[3]):
        cluster.Cluster(nodesChosen)
    elif(algorithmChosen == ALGORITHMS[4]):
        dijkstra.Dijsktra(nodesChosen)
    elif(algorithmChosen == ALGORITHMS[5]):
        floyd.Floyd(nodesChosen)
    elif(algorithmChosen == ALGORITHMS[6]):
        boruvka.Boruvka(nodesChosen)
    else:
        print("Wrong Algorithm Selected.\nPlease Try Again.")

def GUI():
    global numberOfNodes, algorithm
    # initialize tkinter object
    gui = Tk()
    # set title for the window
    gui.title("Shorest Path Finding Program")
    # set size for the window
    gui.geometry("480x530")

    # text space to display messages
    chatlog = Text(gui, bg='white')
    chatlog.config(state=DISABLED)

    
    NO_OF_NODES = [
    "10 nodes",
    "20 nodes",
    "30 nodes",
    "40 nodes",
    "50 nodes",
    "60 nodes",
    "70 nodes",
    "80 nodes",
    "90 nodes",
    "100 nodes",
    ]

    
    textbox = Text(gui, bg='black')
    textbox.place(x=0, y=0, height=500, width=480)

    title = Label(gui, text="SHORTEST PATH FINDING ALGORITHM")
    author1Label = Label(gui, text="19K-1537 Abdul Rehman BSCS-A")

    
    
    numberOfNodes = StringVar(gui)
    numberOfNodes.set(NO_OF_NODES[0]) # default value

    nodesLabel = Label(gui, text="Select the number of nodes: ")
    nodesDropDownList = OptionMenu(gui, numberOfNodes, *NO_OF_NODES)
    nodesDropDownList.pack()
    
    # nodesChosen = int(numberOfNodes.get()[0:2])
    # print("AFTER LIST: NODES= " + str(nodesChosen))
    algorithm = StringVar(gui)
    algorithm.set(ALGORITHMS[0]) # default value

    algorithmLabel = Label(gui, text="Select the algorithm: ")
    algorithmDropDownList = OptionMenu(gui, algorithm, *ALGORITHMS)
    algorithmDropDownList.pack()

    title.place(x=160, y = 30)
    
    author1Label.place(x=180, y = 50)

    nodesLabel.place(x=180, y=120)
    nodesDropDownList.place(x=210, y=140, width=97)
    
    algorithmLabel.place(x=200, y=210)
    algorithmDropDownList.place(x=180, y=240, width=186)
    
    
    print("Nodes: " + numberOfNodes.get())
    print("ALGORITHM: " + algorithm.get())
    # nodesChosen = int(numberOfNodes.get()[0:2])
    # algorithmChosen = algorithm.get()
   
    

    
    # # buttons to send messages
    computeBtn = Button(gui, bg='#E3F6FF', fg='black', text='Compute', command=compute)
    # int(numberOfNodes.get()[0:2]), algorithm.get())
    computeBtn.place(x=210, y=320, width = 100)

    # to keep the window in loop
    gui.mainloop()
    
    


if __name__ == '__main__':
    
    GUI()