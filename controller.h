#include <iostream>
#include <string>


#include "msg.h"

class Controller {
public:
    Controller();

    int exec(Msg, string *);
    int exec(Msg);
    
    int quit();
    int ls();
    int cd();
    int cdup();
    int put();
    int get();
    
private:
    string m_strNowDir;
};
