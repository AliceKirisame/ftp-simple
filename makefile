all: CLIENT SERVER

CC=g++
CFLAG=-c
CLANG=-std=c++11

CLIENT: msg.o msg.h client.h client.cpp
	${CC} ${CLANG} -g msg.o client.cpp -o CLIENT

SERVER: msg.o msg.h server.h server.cpp
	${CC} ${CLANG} -g msg.o server.cpp -o SERVER
	
msg.o: msg.h msg.cpp
	${CC} ${CFLAG} ${CLANG} msg.cpp

clean:
	rm -rf CLIENT SERVER *.o
