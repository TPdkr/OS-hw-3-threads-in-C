/*
This is assignment 3
Done by Timofei Podkorytov
for Operating systems course
in fall 2024
*/
#ifndef NUMAR_H
#define NUMAR_H

/*
NUMAR
A struct for storing a number and its digits
size - the number of digits
num -  the number itself
digits - array of digits
*/
typedef struct numar{
    int size;
    int num;
    int* digits;
} numar;

/*
CREATE NUMAR
create an instance of struct based on a given positive number num
*/
numar createNumar(int num);
/*
GET DIGIT
get a digit from a number based on its place
*/
int getDigit(int num, int pos);
/*
POW INT
power of an integer number
*/
int powInt(int num, int pow);
/*
GET SIZE
get the number of sigits of a number
*/
int getSize(int num);
/*
POW NUMAR
get the sum of all digits of a number raised to a given power
*/
int powNumar(numar num, int pow);
/*
IS PERFECT
is a number perfect? num - a number to check
*/
int isPerfect(int num);
/*
PRINT NUMAR
print the contents of the struct. useful for debugging
*/
void printNumar(numar num);
/*
FREE NUMAR
free the memory of the struct
*/
void freeNumar(numar num);
#endif