# README
This a README file for assignment 3 submitted by Timofei Podkorytov. Here you can find the list of all files included in this folder as well as their descriptions.

## Running the program:
- ./test - for running a predefined time measurement test
- ./main - for user input
- python graph.py - for creating a graph after running ./test

## Makefile:
The following commands are available using the make file. 

```
$ make test
$ make main
$ make all
```

1. make test - make the file test.c main function that measures time
2. make main - make the main function that implements a and b
3. make all - make everything
## Files:
1. Makefile
2. test.c
3. pdi-numbers.c
4. numar.c
5. numar.h
6. utils.c
7. utils.h
8. graph.py
9. graph1.png
### test.c:
Has a main function and is run to count the time it takes to complete the task depending on the number of threads used. It outputs the times it took to execute to the "data.txt" file

### pdi-numbers.c:
This file has a main function and implements the user input functionality described in points a and b, 

### numar.c and numar.h:
These files declare and define a struct as well as a function that is used for checking if a given number is Perfect.
### utils.c and utils.h:
These files contain contain a flags struct as well as functions that make the code work. The key functions are get options(getOptions) and search numbers (searchNum) as they are invoked from the main function.

### graph.py
This file processes the data, that the ./test outputs into a file and creates a smoothed graph that represents the time it took to process depending on thread count. Smoothing the graph makes it more readable and easier to spot the patterns on.
### graph1.png
This is the resulted graph. As you can see overall the time it takes to process decreases. However, on some segments the oposite behaviour is observed. This can be attributed to it taking more time to split the range into pieces. (This file has '1' in its name so it would not get replaced during execution)