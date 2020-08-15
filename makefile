all: CLIENT SERVER BaseController.o ClientController.o

CC=g++
CFLAG=-c
CLANG=-std=c++17

CLIENT: controller.o transmitter.o msg.o client.h client.cpp defines.h
	${CC} ${CLANG} -g transmitter.o msg.o client.cpp -o CLIENT

SERVER: controller.o transmitter.o msg.o server.h server.cpp defines.h
	${CC} ${CLANG} -g controller.o transmitter.o msg.o server.cpp -o SERVER
	
msg.o: msg.h msg.cpp defines.h
	${CC} ${CFLAG} ${CLANG} msg.cpp
	
transmitter.o: transmitter.h transmitter.cpp defines.h
	${CC} ${CFLAG} ${CLANG} transmitter.cpp
	
controller.o: controller.h controller.cpp defines.h
	${CC} ${CFLAG} ${CLANG} controller.cpp
	
BaseController.o: BaseController.h BaseController.cpp defines.h
	${CC} ${CFLAG} ${CLANG} BaseController.cpp
	
ClientController.o: ClientController.h ClientController.cpp defines.h
	${CC} ${CFLAG} ${CLANG} ClientController.cpp

clean:
	rm -rf *.o CLIENT SERVER
