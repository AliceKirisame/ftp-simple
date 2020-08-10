#include "msg.h"

Msg::Msg() {}

Msg::Msg(int l, Msg::Com c):m_iLength(l), m_eCommand(c) {}

Msg::Msg(int l, string s):m_iLength(l) {
    
    m_eCommand = getComId(s);
    
}

Msg::Com getComId(string s) {
    
    if(s == "quit") return Msg::QUIT;
    if(s == "ls") return Msg::LS;
    if(s == "cd") return Msg::CD;
    if(s == "cd..") return Msg::CDUP;
    if(s == "put") return Msg::PUT;
    if(s == "get") return Msg::GET;
    
    return Msg::UNKNOWN;
    
}
