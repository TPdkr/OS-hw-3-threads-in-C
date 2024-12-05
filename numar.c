/*
This is assignment 3
Done by Timofei Podkorytov
for Operating systems course
in fall 2024
*/
#include "numar.h"
#include <stdio.h>
#include <stdlib.h>

//POW INT
int powInt(int num, int pow){
    int n=1;
    for(int i=0;i<pow;i++){
        n*=num;
    }
    return n;
}

//GET DIGIT
int getDigit(int num, int pos){
    return (num % powInt(10, pos+1))/powInt(10,pos);
}

//GET SIZE
int getSize(int num){
    int size=0;
    for(;powInt(10,size)<=num;size++){}
    return size;
}

//CREATE NUMAR
numar createNumar(int num){
    numar newnum;
    newnum.num=num;
    newnum.size=getSize(num);
    newnum.digits=(int*) malloc(sizeof(int)*newnum.size);
    //memory allocation check
    if (newnum.digits==NULL){
        fprintf(stderr, "pdi-numbers: memory allocation error\n");
        exit(1);
    }
    //we fill the array with digits
    for(int i=0;i<newnum.size;i++){
        newnum.digits[i]=getDigit(newnum.num, i);
    }
    return newnum;
}

//POW NUMAR
int powNumar(numar num, int pow){
    int sum=0;//sum return variable
    //we add each digit raised to the given power
    for(int i = 0; i<num.size; i++){
        sum+=powInt(num.digits[i], pow);
    }
    return sum;
}

//IS PERFECT?
int isPerfect(int num){
    numar n = createNumar(num);
    int prpow=0;//previous sum power
    int pow=-1;//power
    int curpow=0;//current sum power
    //while the sum rises and its smaller than a number it makes sense to search
    do{
        pow++;
        prpow=curpow;//we shift the current to previous
        curpow=powNumar(n,pow);//we recalculate current
    } while (curpow<num && curpow-prpow>0);
    //freeing used memory
    freeNumar(n);
    //we check the last sum
    return curpow==num;

}

//PRINT NUMAR
void printNumar(numar num){
    //can be used for debugging
    printf("Number: %d\nHas %d digits\n", num.num, num.size);
    printf("Digits: ");
    for (int i=0;i<num.size;i++){
        printf("%d ", num.digits[i]);
    }
    printf("\n");
}

//FREE NUMAR
void freeNumar(numar num){
    free(num.digits);
}