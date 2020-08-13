all: CLIENT SERVER

CC=g++
CFLAG=-c
CLANG=-std=c++17

CLIENT: controller.o transmitter.o msg.o client.h client.cpp
	${CC} ${CLANG} -g transmitter.o msg.o client.cpp -o CLIENT

SERVER: controller.o transmitter.o msg.o server.h server.cpp
	${CC} ${CLANG} -g controller.o transmitter.o msg.o server.cpp -o SERVER
	
msg.o: msg.h msg.cpp
	${CC} ${CFLAG} ${CLANG} msg.cpp
	
transmitter.o: transmitter.h transmitter.cpp
	${CC} ${CFLAG} ${CLANG} transmitter.cpp
	
controller.o: controller.h controller.cpp
	${CC} ${CFLAG} ${CLANG} controller.cpp

clean:
	rm -rf *.o CLIENT SERVER
