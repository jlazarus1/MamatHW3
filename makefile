####################################################################
# Makefile for building the calc application
#


#
# Definitions
#
CC = gcc
CFLAGS = -g -Wall
CCLINK = $(CC)
OBJS = main.o expTree.o polishCalc.o
RM = rm -f
TARGET = calc


#
# Target Section
#
$(TARGET): $(OBJS)
	$(CCLINK) -o $(TARGET) $(OBJS)


#
# File Section
#
main.o: main.c defs.h polishCalc.h
expTree.o: expTree.c defs.h expTree.h
polishCalc.o: polishCalc.c polishCalc.h polishCalcTypes.h expTree.h


#
# Cleaning
#
clean:
	$(RM) $(TARGET) *.o *.bak *~"#"* core
