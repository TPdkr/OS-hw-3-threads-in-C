/*
This is assignment 3
Done by Timofei Podkorytov
for Operating systems course
in fall 2024
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
 #include <time.h>
#include "utils.h"
/*
This file is used for testing the -t flag and the performance of the programm
*/
//MAIN-------------------------------------------------------------------------
int main(){
    flags flag;//flags struct
    int maxPar=1000;//maximum thread count
    double timeUsed;
    clock_t start;//for storing clock values
    clock_t end;
    FILE* data;//output file

    //We set the range and other flag values
    flag.start=1;
    flag.end=100000;
    flag.writeTrace=0;
    flag.test=1;//we do not want to see numbers in terminal
    flag.par=maxPar;

    //we open the file
    data=fopen("data.txt", "w");
    fprintf(data,"%d\n", flag.end);
    if (data==NULL){//check that opened correctly
        fprintf(stderr,"Error opening file");
        exit(1);
        
    }
    //we measure time
    for(int i=1;i<=maxPar;i++){
        start=clock();//remember start time
        flag.par=i;
        searchNum(flag);
        end=clock();//remember finish time
        timeUsed = ((double) (end - start)) / CLOCKS_PER_SEC;
        fprintf(data,"%lf\n", timeUsed);//output result
    }
    //close the output file
    fclose(data);
    return 0;
}

