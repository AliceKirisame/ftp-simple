#ifndef MSG_H
#define MSG_H

#include <iostream>
#include <string>

#include "defines.h"

using namespace std;

class Msg {
public:
    
    enum Com {
        QUIT, LS, CD, CDUP, PUT, GET, UNKNOWN
    } m_eCommand;
    
    int m_iLength;
    
    Msg();
    Msg(Com c, int l);
    Msg(string s, int l);
    Msg(int l);
    
    Com getComId(string s);
    int setDataLength(int);
    int setCommmand(Com);
};

#endif
