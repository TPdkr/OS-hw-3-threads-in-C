/*
This is assignment 3
Done by Timofei Podkorytov
for Operating systems course
in fall 2024
*/

#ifndef UTILS_H
#define UTILS_H

/*
UTILS.H
STRUCT
Here i defined a trcut for storing flags that are passed

end - until what number we check
start from what number we start
par - parallel execution
writeTrace - do we write trace
test - in case of time test no need to print to stdout
*/
typedef struct flags{
    int end;
    int start;
    int par;
    int writeTrace;
    int test;
} flags;
/*
GET POSITIVE INT
This function is used for user input to get a positive integer
*/
void getPosInt(int* num, char flag, char inp[]);
/*
GET OPTIONS
This function gets the flags and handles the options. It changes the variables
in accordance with the choice of the user.
char* argv-argument list
int argc-number of arguments
flags flag-a pointer to where the input flags will be stored
*/
void getOptions(char* argv[], int argc, flags* flag);

/*
CHECK RANGE
This function checks a gievn range and prints numbers that are perfect
int s - start
int e - end
*/
void* checkRange(void* range);

/*
CHUNK RANGE
This function splits the given range into chunks according to the number of
parallel processes that can run.
flags flag - flags from input
*/
int** chunkRange(flags flag);

/*
SEARCH NUMBERS
This function checks the range by chunking it into several pieces via chunk
range and processing them concurrently.
flags flag - flags from input
*/
void searchNum(flags flag);
#endif