#ifndef BASECONTROLLER_H
#define BASECONTROLLER_H

#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <exception>

#include "msg.h"
#include "transmitter.h"

using namespace std;
using namespace std::filesystem;

class BaseController {
public:
    
    BaseController(string, int);
    BaseController(string);
    ~BaseController();
    
    virtual int Transmit() = 0;
    
    virtual int Exec();
    
    virtual int Quit();
    
    virtual int Ls() = 0;

    virtual int Cd() = 0;
    
    virtual int Cdup() = 0;

    virtual int Put() = 0;

    virtual int Get() = 0;
    
    int setSocketFD(int);
    
protected:
    
    Msg m_Msg;
    
    path m_phNowDir;
    vector<string> m_vecFiles;
    string m_strFileList;
    
    string m_strTargetFileName;
    int m_iTargetDataLength;
    
    int m_iSocketFD;
    
    Transmitter m_Transer;
};

#endif
