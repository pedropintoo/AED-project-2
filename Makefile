# To compile all programs, run:
#   make
#
# AED, ua, 2023

CC = gcc
CFLAGS += -g -Wall -Wextra
CPPFLAGS += -MMD

TARGETS = example1 example2 example3 example4 GraphTestTopoSuccess GraphTestTopoInsuccessBest GraphTestTopoInsuccessWorst

all: $(TARGETS)

example1: example1.o Graph.o SortedList.o instrumentation.o

example2: example2.o Graph.o GraphTopologicalSorting.o \
 IntegersQueue.o SortedList.o instrumentation.o

example3: example3.o Graph.o GraphTopologicalSorting.o \
 IntegersQueue.o SortedList.o instrumentation.o

example4: example4.o Graph.o SortedList.o GraphGenerator.o \
 instrumentation.o GraphTopologicalSorting.o IntegersQueue.o

GraphTestTopoSuccess: GraphTestTopoSuccess.o Graph.o GraphTopologicalSorting.o \
 IntegersQueue.o GraphGenerator.o SortedList.o instrumentation.o

GraphTestTopoInsuccessBest: GraphTestTopoInsuccessBest.o Graph.o GraphTopologicalSorting.o \
 IntegersQueue.o GraphGenerator.o SortedList.o instrumentation.o

GraphTestTopoInsuccessWorst: GraphTestTopoInsuccessWorst.o Graph.o GraphTopologicalSorting.o \
 IntegersQueue.o GraphGenerator.o SortedList.o instrumentation.o

# Include dependencies (generated with gcc -MMD)
-include *.d


# Cleanup
clean:
	rm -f *.o *.d
	rm -f $(TARGETS)

