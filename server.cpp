#include "server.h"

Server::Server(int port) {

    bzero(&m_sServeraddr, sizeof(m_sServeraddr));
    
    m_sServeraddr.sin_family = AF_INET;
    m_sServeraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    m_sServeraddr.sin_port = htons(port);
    
    m_iPort = port;
    m_iClientaddr_size = sizeof(sockaddr_in);
    
    m_pcBuffer = new char[MAX_LENGTH];
    
    Init();
}

Server::Server():Server(9987) {}

Server::~Server() {
    
    Close();
    delete []m_pcBuffer;
}

int Server::Init() {
    
#ifdef DEBUG
    cout << endl << "debug mode" << endl << endl;
#endif
    
    if((m_iListenFD = socket(AF_INET, SOCK_STREAM, 0)) == -1) printf("creating socket error\n");
       
    if((bind(m_iListenFD, (sockaddr *)&m_sServeraddr, sizeof(m_sServeraddr)) == -1)) printf("binding socket error\n");
    
    if(listen(m_iListenFD, WAITING_NUM) == -1) printf("listen socket error\n");
    
    return 0;
}

int Server::Listen() {
    
    while(1) {
        
        cout << m_iListenFD << " waiting for connection" << endl;
        
        if((m_iAcceptFD = accept(m_iListenFD, (sockaddr *)NULL, NULL)) < 0) {
            cout << "accepting error" << endl; 
            return -1;
        }
        
        cout << "connected, accepted Fd:" << m_iAcceptFD << endl << endl;

        Transmit(m_iAcceptFD);
        
    }
    
    return 0;
}

int Server::Transmit(int m_iAcceptFD) {

    Controller controller(".", m_iAcceptFD);

    controller.Exec();
    
    cout << "disconnected, closing FD" << endl << endl;
    close(m_iAcceptFD);
    
    return 0;
    
}

int Server::Close() {
    
    close(m_iListenFD);
    
    return 0;
}

int main(int argc, char **argv) {
    
    if(argc != 2) {
        cout << "Usage: filename [port]" << endl;
        
        return -1;
    }
    
    Server srv = Server(atoi(argv[1]));
    srv.Listen();
    
    return 0;
}
