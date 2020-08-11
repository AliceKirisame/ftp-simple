#include <iostream>
#include <string>

using namespace std;

#define MAX_LENGTH 2048

class Msg {
public:
    
    enum Com {
        QUIT, LS, CD, CDUP, PUT, GET, UNKNOWN
    } m_eCommand;
    
    int m_iLength;
    
    Msg();
    Msg(int l, Com c);
    Msg(int l, string s);
    Msg::Com getComId(string s);
};


