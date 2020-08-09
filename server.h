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


#include "msg.h"

using namespace std;

class Server {
public:
    Server();
    ~Server();
    
    int Listen();
    int Init();
    int Close();
    const int PORT{30000};
    const int WAITING_NUM{3};
    
private:
    int m_iListenFD;
    int m_iAcceptFD;
    socklen_t m_iClientaddr_size;
    socklen_t m_iServeraddr_size;
    
    struct sockaddr_in m_sServeraddr;
    struct sockaddr_in m_sClientaddr;
    
    char *m_pcBuffer;
    string m_strData;
    
};