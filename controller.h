#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <exception>
#include <fstream>

#include "msg.h"
#include "transmitter.h"

using namespace std;
using namespace std::filesystem;

class Controller {
public:
    
    Controller(string);
    Controller(string, int);
    ~Controller();
    
    int Exec();
    
    int Quit();
    int Ls();
    int Cd(int);
    int Cdup();
    int Put(int);
    int Get(int);
    
    int setSocketFD(int);
    
private:
    path m_phNowDir;
    vector<string> m_vecFiles;
    string m_strFileList;
    
    int m_iSocketFD;
    
    Transmitter m_Transer;
};

#endif
