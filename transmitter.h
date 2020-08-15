#ifndef TRANSMITTER_H
#define TRANSMITTER_H

#include <iostream>
#include <string>
#include <string.h>
#include <unistd.h>
#include <fstream>

#include "msg.h"

using namespace std;

class Transmitter {
public:
    
    Transmitter(int);
    Transmitter();
    ~Transmitter();
    
    int sendStr(string &);
    int receiveStr(string &, int);
    
    int Send(const void *, int);
    void * Receive(int);
    int Receive(void *, int);

    int sendFile(ifstream &, int);
    int receiveFile(ofstream &, int);
    
    bool getIsConnected();
    bool setIsConnected(bool);
    int setSocketFD(int);
    
    int errorExit(string);
    
private:
    bool m_bIsConnected;
    int m_iSocketFD;
    char *m_pcBuffer;
};

#endif
