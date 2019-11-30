# This is a makefile for the person database system
CC = gcc
CFLAGS = -g -Wall
CCLINK = $(CC)
LIBS = 
OBJS = main.o airport.o runway.o flight.o
RM = rm -f

# Creating the executables
airport: $(OBJS)
	$(CCLINK) -o airport $(OBJS) $(LIBS)

# Creating object files using default rules
airport.o: airport.c airport.h ex2.h runway.h flight.h
flight.o: flight.c flight.h ex2.h
main.o: main.c airport.h ex2.h runway.h flight.h
runway.o: runway.c runway.h ex2.h flight.h

# Cleaning old files before new make
clean:
	$(RM) airport screen_test *.o *.bak *~ "#"* core
