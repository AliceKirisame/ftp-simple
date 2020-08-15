#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <exception>

#include "msg.h"
#include "transmitter.h"

using namespace std;
using namespace std::filesystem;

class Controller {
public:
    
    Controller(string, int);
    Controller(string);
    Controller(int);
    ~Controller();
    
    virtual int Transmit() = 0;
    
    virtual int Exec();
    
    virtual int Quit();
    
    virtual int Ls() = 0;

    virtual int Cd() = 0;
    
    virtual int Cdup() = 0;

    virtual int Put() = 0;

    virtual int Get() = 0;
    
    virtual int Unknown() = 0;
    
    int setSocketFD(int);
    
protected:
    
    Msg m_Msg;
    
    path m_phNowDir;
    vector<string> m_vecFiles;
    string m_strFileList;
    
    string m_strTargetData;
    int m_iTargetDataLength;
    
    int m_iSocketFD;
    
    Transmitter m_Transer;
};

#endif
