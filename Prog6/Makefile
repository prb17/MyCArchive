all: piper

piper: piper.o Command.o ExecutionPair.o
	g++ -Wall -g -o piper piper.o Command.o ExecutionPair.o

ExecutionPair.o: ExecutionPair.cpp ExecutionPair.h
	g++ -Wall -g -c ExecutionPair.cpp

Command.o: Command.cpp Command.h
	g++ -Wall -g -c Command.cpp

piper.o: piper.cpp Command.o ExecutionPair.o
	g++ -Wall -g -c piper.cpp

clean:
	rm -f piper.o Command.o ExecutionPair.o