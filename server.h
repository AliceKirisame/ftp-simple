#include <unistd.h>
#include <iostream>
#include <string>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <sys/stat.h>
#include <fcntl.h>
#include <exception>

#include "msg.h"
#include "transmitter.h"
#include "controller.h"

using namespace std;

class Server {
public:
    Server();
    Server(int); 
    ~Server();
    
    int Listen();
    int Init();
    int Transmit(int);
    int Close();
    
    const int WAITING_NUM{3};
    
private:
    
    int m_iPort{30001};
    
    int m_iListenFD;
    int m_iAcceptFD;
    socklen_t m_iClientaddr_size;
    socklen_t m_iServeraddr_size;
    
    struct sockaddr_in m_sServeraddr;
    struct sockaddr_in m_sClientaddr;

    
    char *m_pcBuffer;
    string m_strData;
    
};
