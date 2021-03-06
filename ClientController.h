#ifndef CLIENTCONTROLLER_H
#define CLIENTCONTROLLER_H

#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <exception>
#include <fstream>

#include "msg.h"
#include "transmitter.h"
#include "Controller.h"

class ClientController : public Controller {
public:
    ClientController(string);
    ClientController(string, int);
    ClientController(int);
    ~ClientController();
    
    virtual int Transmit();
    
    virtual int Ls();

    virtual int Cd();
    
    virtual int Cdup();

    virtual int Put();

    virtual int Get();
    
    virtual int Unknown();
};

#endif
