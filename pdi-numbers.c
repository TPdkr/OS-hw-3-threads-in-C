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
#include "utils.h"

//MAIN-------------------------------------------------------------------------
int main(int argc, char* argv[]){
    flags flag;//flags struct
    getOptions(argv,argc,&flag);
    searchNum(flag);
    return 0;
}

