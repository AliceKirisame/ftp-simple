all: CLIENT SERVER

CC=g++
CFLAG=-c
CLANG=-std=c++11

CLIENT: client.h client.cpp
	${CC} ${CLANG} client.cpp -o CLIENT

SERVER: server.h server.cpp
	${CC} ${CLANG} server.cpp -o SERVER
	

