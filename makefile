# Make file for Assignment 11

CC	= g++ -Wall -pedantic -Wextra -std=c++11 -g

OBJS = ladder.o wordLadderImp.o
DEPS1 = linkedQueue.h
DEPS2 = linkedStack.h
DEPS3 = wordLadder.h


all: ladder

ladder: $(OBJS)
	$(CC) -o ladder $(OBJS)


ladder.o: ladder.cpp $(DEPS3)
	$(CC) -c ladder.cpp


wordLadderImp.o: wordLadderImp.cpp $(DEPS1) $(DEPS2) $(DEPS3)
	$(CC) -c wordLadderImp.cpp

# -----
#  clean by removing object files.

clean:
	$(RM) $(DOBJS)
	$(RM) $(OBJS)

