#Author: Carlos Carrillo
#Date:   11/25/2015
#Description: This is the makefile for Lab_9

#This target will compile the entire program

All: total

total:	STLContainers.o 
	g++ STLContainers.o -o stl

STLContainers.o: STLContainers.cpp
	g++ -c STLContainers.cpp

clean:
	rm -rf *o total