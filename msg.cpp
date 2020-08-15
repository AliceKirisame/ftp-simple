#include "msg.h"

Msg::Msg() {}

Msg::Msg(Msg::Com c, int l):m_iLength(l), m_eCommand(c) {}

Msg::Msg(string s, int l):m_iLength(l) {
    
    m_eCommand = getComId(s);
    
}

Msg::Msg(int l) : Msg(Msg::UNKNOWN, l) {}

Msg::Com Msg::getComId(string s) {
    
    if(s == "quit") return Msg::QUIT;
    if(s == "ls") return Msg::LS;
    if(s == "cd") return Msg::CD;
    if(s == "cd..") return Msg::CDUP;
    if(s == "put") return Msg::PUT;
    if(s == "get") return Msg::GET;
    
    return Msg::UNKNOWN;
    
}

int Msg::setDataLength(int l) {
    return m_iLength = l;
}

int Msg::setCommmand(Msg::Com c) {
    m_eCommand = c;
    return 0;
}
