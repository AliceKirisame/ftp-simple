#ifndef CLIENTCONTROLLER_H
#define CLIENTCONTROLLER_H

#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <exception>

#include "msg.h"
#include "transmitter.h"
#include "BaseController.h"

class ClientController : public BaseController {
    
    ClientController(string);
    ClientController(string, int);
    ~ClientController();
    
    virtual int Transmit();
    
    virtual int Ls();

    virtual int Cd();
    
    virtual int Cdup();

    virtual int Put();

    virtual int Get();
};

#endif
