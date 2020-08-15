#ifndef SERVER_CONTROLLER_H
#define SERVER_CONTROLLER_H

#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <exception>
#include <fstream>

#include "msg.h"
#include "transmitter.h"
#include "Controller.h"

class ServerController : public Controller {
    
public:
    ServerController(string, int);
    ServerController(string);
    ServerController(int);
    
    ~ServerController();
    
    virtual int Transmit();
    
    virtual int Ls();

    virtual int Cd();
    
    virtual int Cdup();

    virtual int Put();

    virtual int Get();
    
    virtual int Unknown();
    
};


#endif
