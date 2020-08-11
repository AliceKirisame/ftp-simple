#include <unistd.h>
#include <iostream>
#include <string>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include<netinet/in.h>
#include <arpa/inet.h>

#include <sys/stat.h>
#include <fcntl.h>

#include <exception>

#include "msg.h"

using namespace std;

class Client {
public:
    Client(string addr, int port);
    ~Client();
    
    int Connect();
    int Close();

private:
    struct sockaddr_in m_sClientaddr;
    struct sockaddr_in m_sServeraddr;
    
    int m_iSocketFD;
    int m_iConnetFD;
    
    char *m_pcBuffer;
    string m_strData;
};
