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
#include <pthread.h>
#include "utils.h"
#include "numar.h"

//GET POSITIVE INT-------------------------------------------------------------
void getPosInt(int* num, char flag,char inp[]){
    int suc=sscanf(inp, "%d", num);
    //is the arguemnt int check
    if (suc!=1){
        fprintf(stderr, "pdi-numbers: invalid number %s for -%c option\n", inp,flag);
        exit(1);
    }
    //invalid int check
    if(*num<=0){
        fprintf(stderr,"pdi-numbers: value %d for -%c option should be >= 1\n", *num,flag);
        exit(1);
    }
}
//GET OPTIONS------------------------------------------------------------------
void getOptions(char* argv[], int argc, flags* flag){
    //the argument position
    int argPos=1;
    //we set default values
    flag->par=1;
    flag->end=10000;
    flag->start=1;
    flag->writeTrace=0;
    flag->test=0;
    int opt;
    //we use getopt for options
    while((opt = getopt(argc, argv, ":vs:e:t:"))!=-1){
        switch(opt){
            case 'v'://write trace
                flag->writeTrace=1;
                argPos++;
                break;
            case 's'://start
                getPosInt(&flag->start,'s',optarg);
                argPos+=2;
                break;
            case 'e'://end
                getPosInt(&flag->end,'e',optarg);
                argPos+=2;
                break;
            case 't'://parallel
                getPosInt(&flag->par,'t',optarg);
                argPos+=2;
                break;
            case ':'://nothing to be done but call an error
            case '?'://unknown flag meaning invalid input
                fprintf(stderr,"pdi-numbers: invalid option '%c'\n", opt);
                exit(1);
                break;
        }
    }
    //is there still something left? ERROR in input
    if(argv[argPos]!=NULL){
        fprintf(stderr,"pdi-numbers: too many arguments supplied\n");
        exit(EXIT_FAILURE);
    }
    //in case of invalid input of range
    if(flag->start>flag->end){
        fprintf(stderr,"pdi-numbers: start can't be after end\n");
        exit(EXIT_FAILURE);
    }
    //in case of too many threads given
    if(flag->end-flag->start+1<flag->par){
        flag->par=flag->end-flag->start+1;
    }
}

//CHECK RANGE------------------------------------------------------------------
void* checkRange(void* range){
    flags* flag = (flags*) range;
    for(int i=flag->start; i<=flag->end;i++){
        //we use another function to see if the number is perfect
        if(isPerfect(i)){
            //we print when not measuring time(testing)
            !flag->test ? printf("%d\n", i):(1);
        }
    }
    return NULL;
}

//CHUNK RANGE------------------------------------------------------------------
int** chunkRange(flags flag){
    int size=flag.end-flag.start+1;//the range size
    int chunk=size/flag.par;//chunk size
    int** ranges = (int**) malloc(sizeof(int*)*flag.par);
    //check for correct allocation
    if(ranges==NULL){
        fprintf(stderr, "pdi-numbers: memory allocation error\n");
        exit(1);
    }
    for(int i=0;i<flag.par;i++){
        ranges[i]=(int*) malloc(sizeof(int)*2);
        if(ranges[i]==NULL){
            fprintf(stderr, "pdi-numbers: memory allocation error\n");
            exit(1);
        }
    }
    //seting the ranges
    for(int i=0;i<flag.par;i++){
        ranges[i][0]=chunk*i+flag.start;
        if(i+1!=flag.par){
            //regular case
            ranges[i][1]=chunk*(i+1)+flag.start-1;
        } else{
            //special case of the last subrange
            ranges[i][1]=flag.end;
        }
    }
    return ranges;
}

//SEARCH NUMBERS---------------------------------------------------------------
void searchNum(flags flag){
    pthread_t tid[flag.par];//thread ids
    flags tempFlag[flag.par];//flags for each thread
    int** ranges = chunkRange(flag);//we chunk the given range
    //we srart the processes
    for(int i=0;i<flag.par;i++){
        //we copy range and flag data about range and test
        tempFlag[i].start=ranges[i][0];
        tempFlag[i].end=ranges[i][1];
        tempFlag[i].test=flag.test;
        //trace is printed
        (flag.writeTrace)? fprintf(stderr,"pdi-numbers: t%d searching [%d,%d]\n"\
        ,i,tempFlag[i].start,tempFlag[i].end):(1);
        //we create thread
        int rc = pthread_create(&tid[i], NULL, checkRange, &tempFlag[i]);
        if(rc != 0){
			fprintf(stderr, "pdi-numbers: pthread_create failed\n");
			exit(EXIT_FAILURE);
		}
    }
    //we wait for them to finish
    for(int i=0;i<flag.par;i++){
        //joining all threads and waiting for correctness
        int rc = pthread_join(tid[i], NULL);
		if(rc!=0){
			fprintf(stderr, "pdi-numbers: pthread_join failed\n");
			exit(EXIT_FAILURE);
		}
        //printing trace
        (flag.writeTrace)? fprintf(stderr,"pdi-numbers: t%d finishing\n"\
        ,i):(1);
    }
    //freeing the allocated memory
    for(int i=0;i<flag.par;i++){
        free(ranges[i]);
    }
    free(ranges);
}