#include "server.h"

Server::Server(int port) {
//     m_iListenFD = socket(AF_INET, SOCK_STREAM, 0);
//     :
//     }
//     catch(int) {
//         cout << "creating socket error" << endl;
//     }

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
        Transmitter::setIsConnected(true);
        
        Transmit(m_iAcceptFD);
        
    }
    
    return 0;
}

int Server::Transmit(int m_iAcceptFD) {
    
//     Msg msg;
//     Transmitter transer(m_iAcceptFD);

    Controller controller(".", m_iAcceptFD);

    controller.Exec();
    
    return 0;
//     try {
// 
//         while(transer.getIsConnected()) {
//             
//             if(transer.Receive(&msg, sizeof(msg)) < 0) break;
//             
//             cout << "command id:" << msg.m_eCommand << endl;
//             
//             if(msg.m_eCommand >= Msg::UNKNOWN || msg.m_eCommand < 0) {
//                 
//                 m_strData = "unknown command";
// 
//             }
//             
//             else if(msg.m_eCommand == Msg::QUIT) {
//                 break;
//             }
//             
//             else {
//                 int data_length = (msg.m_iLength);
//                 cout << "data_length:" << data_length << endl;
//                 
//                 m_strData = string("the command is ");
//                 
//                 transer.receiveStr(m_strData, data_length);
//             }
//             
//             cout << m_strData << endl << endl;
//             
//             msg.m_iLength = m_strData.size();
//             transer.Send(&msg, sizeof(msg));
//             transer.Send(m_strData.c_str(), strlen(m_strData.c_str()));
//             
//         }
//         
//     }
//     catch(...) {
//         cout << "???" << endl;
//         close(m_iAcceptFD);
//     }
//     
//     cout << "disconnected, closing FD" << endl << endl;
//     close(m_iAcceptFD);
    
    
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
