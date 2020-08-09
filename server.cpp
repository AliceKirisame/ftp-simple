#include "server.h"

Server::Server() {
//     m_iListenFD = socket(AF_INET, SOCK_STREAM, 0);
//     
//     try{
//         if(m_iListenFD == -1) throw -1;
//     }
//     catch(int) {
//         cout << "creating socket error" << endl;
//     }

    bzero(&m_sServeraddr, sizeof(m_sServeraddr));
    
    m_sServeraddr.sin_family = AF_INET;
    m_sServeraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    m_sServeraddr.sin_port = htons(PORT);
    
    m_iClientaddr_size = sizeof(sockaddr_in);
    
    m_pcBuffer = new char[MAX_LENGTH];
    
    Init();
}

Server::~Server() {
    Close();
    delete []m_pcBuffer;
}

int Server::Listen() {
    
    while(1) {
        
        cout << m_iListenFD << " waiting for connection" << endl;
        
        if((m_iAcceptFD = accept(m_iListenFD, (sockaddr *)NULL, NULL)) < 0) {
            cout << "accepting error" << endl; 
            return -1;
        }
        
        
        cout << "connected, accepted Fd:" << m_iAcceptFD << endl;
        bool isConnected = true;
        Msg msg(0);
        
        while(isConnected) {
        
            read(m_iAcceptFD, &msg, sizeof(msg));
            
            int data_length = (msg.length);
            cout << data_length << endl;
            
            m_strData = string();
            
            while(data_length != 0) {
                
                bzero(m_pcBuffer, sizeof(m_pcBuffer));
                int recv_length = read(m_iAcceptFD, m_pcBuffer, MAX_LENGTH - 1);
                
                if(recv_length <= 0) {
                    data_length = 0;
                    isConnected = false;
                    cout << "disconneted. closing" << endl;
                }
            
                m_strData.append(m_pcBuffer);
                
                data_length -= recv_length;
            }
            cout << m_strData << endl;
            write(m_iAcceptFD, m_strData.c_str(), strlen(m_strData.c_str()));
        }
    
        close(m_iAcceptFD);
    }
    
    return 0;
}

int Server::Init() {
    
    if((m_iListenFD = socket(AF_INET, SOCK_STREAM, 0)) == -1) printf("creating socket error\n");
       
    if((bind(m_iListenFD, (sockaddr *)&m_sServeraddr, sizeof(m_sServeraddr)) == -1)) printf("binding socket error\n");
    
    if(listen(m_iListenFD, WAITING_NUM) == -1) printf("listen socket error\n");
    
    return 0;
}

int Server::Transmit() {
    
    return 0;
}

int Server::Close() {
    
    close(m_iListenFD);
    
    return 0;
}

int main() {
    
    Server srv = Server();
    srv.Listen();
    
    return 0;
}
