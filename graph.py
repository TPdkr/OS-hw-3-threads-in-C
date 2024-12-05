'''
This is assignment 3
Done by Timofei Podkorytov
for Operating systems course
in fall 2024
'''
import numpy as np
import matplotlib.pyplot as plt
'''
In this file I plot the data from a data.txxt file
'''

'''
SMOOTH
This function make the data more readable on a graph by averaging
the nearby values
It takes in an array and the radius that we average
'''
def smooth(a, smth):
    b=[]
    for i in range(len(a)):
        sumNum=0.0
        n=0
        if(i<smth):#close to the beginning
            sumNum+=sum(a[:i+smth])
            n+=len(a[:i+smth])
        elif (i>len(a)-smth):#close to the end
            sumNum+=sum(a[i-smth:])
            n+=len(a[i-smth:])
        else:#middle
            sumNum+=sum(a[i-smth:i+smth])
            n+=len(a[i-smth:i+smth])
        b.append(sumNum/n)
    return b

#we open the file and read data
file=open("data.txt")
data=file.readlines()
data=[float(el) for el in data]
#this the max number we search
n=int(data[0])
#this is the actual time values
data=data[1:]
#we smooth the data
data =smooth(data,20)
#arguements array
x=np.linspace(1,len(data),len(data))
#The data for the plot
title="Search time of " + str(n) +" perfect numbers"
color="purple"
xaxis="threads"
yaxis="time (s)"
#We plot and save the graph
plt.plot(x,np.array(data),color=color)
plt.title(title)
plt.xlabel(xaxis)
plt.ylabel(yaxis)
plt.grid()
plt.savefig("graph.png")
file.close()