import turtle
import tkinter as tkinter
import math
root = tkinter.Tk()
root.geometry('500x500-5+40') #added by me
cv = turtle.ScrolledCanvas(root, width=900, height=900)
cv.pack()

screen = turtle.TurtleScreen(cv)
screen.screensize(2000,2000) #added by me
x = (20, 30)
y = (20, 40)
t = turtle.RawTurtle(screen)
t.setheading(-230)
t.forward(100)
root.mainloop()

