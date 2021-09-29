# Connecting Four
## Introduction
**Connect Four** is a two‐player connection game in which the players first choose a color
and then take turns dropping one colored disc from the top into a seven‐column, six‐row vertically
suspended grid. The pieces fall straight down, occupying the lowest available space within the column.
The objective of the game is to be the first to form a horizontal, vertical, or diagonal line of four of
one's own discs.  
![Connecting_Four](https://raw.githubusercontent.com/YangYeh-PD/Connecting_Four/master/Connecting_Four.jpg)

## Input Restrictions
Inputs must be number in **[0, 6]**  
**Cannot** be out of range or be a string

## Sample Input and Output
![Sample_1](https://raw.githubusercontent.com/YangYeh-PD/Connecting_Four/master/Sample_1.jpg)  
![Sample_2](https://raw.githubusercontent.com/YangYeh-PD/Connecting_Four/master/Sample_2.jpg)  
Connecting lines are annotated in **Lower Case**

- Compile Message in Linux  
For C/C++  
```
gcc -o Connecting_Four Connecting_Four.c
./Connecting_Four
```
```
g++ -c Board.cpp Board.h
g++ -c Connecting_Four.cpp Board.h
g++ -o Connecting_Four Connecting_Four.o Board.o
./Connecting_Four
```
You also can use the command `make` to compile it automatically, 
use `make clean` to clean all out files and execution files.