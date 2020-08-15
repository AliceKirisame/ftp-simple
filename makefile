all: CLIENT SERVER
CC=g++
CFLAG=-c
CLANG=-std=c++17

CLIENT: ClientController.o Controller.o transmitter.o msg.o client.h client.cpp defines.h
	${CC} ${CLANG} -g Controller.o ClientController.o transmitter.o msg.o client.cpp -o CLIENT

SERVER: ServerController.o Controller.o transmitter.o msg.o server.h server.cpp defines.h
	${CC} ${CLANG} -g Controller.o ServerController.o transmitter.o msg.o server.cpp -o SERVER
	
msg.o: msg.h msg.cpp defines.h
	${CC} ${CFLAG} ${CLANG} msg.cpp
	
transmitter.o: transmitter.h transmitter.cpp defines.h
	${CC} ${CFLAG} ${CLANG} transmitter.cpp
	
controller.o: controller.h controller.cpp defines.h
	${CC} ${CFLAG} ${CLANG} controller.cpp
	
Controller.o: Controller.h Controller.cpp defines.h
	${CC} ${CFLAG} ${CLANG} Controller.cpp
	
ClientController.o: Controller.o ClientController.h ClientController.cpp defines.h
	${CC} ${CFLAG} ${CLANG} ClientController.cpp
	
ServerController.o: Controller.o ServerController.h ServerController.cpp defines.h
	${CC} ${CFLAG} ${CLANG} ServerController.cpp

clean:
	rm -rf *.o CLIENT SERVER
