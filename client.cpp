#include "client.h"

Client::Client(string addr, int port) {

    try {
        m_iSocketFD = socket(AF_INET, SOCK_STREAM, 0);

        if(m_iSocketFD == -1)
            throw m_iSocketFD;
    }
    catch(int) {
        cout << "error in create socket" << endl;
    }
    
    bzero(&m_sServeraddr, sizeof(m_sServeraddr));
    m_sServeraddr.sin_family = AF_INET;
    m_sServeraddr.sin_port = htons(port);
    
    try {
        if(inet_pton(AF_INET, addr.c_str(), &m_sServeraddr.sin_addr) <= 0)
            throw -1;
    }
    catch(int) {
        cout << "error in inet_pton" << endl;
    }
    
    m_pcBuffer = new char[MAX_LENGTH];
}

Client::~Client() {
    
    delete []m_pcBuffer;
}

int Client::Connect() {
    
    if(connect(m_iSocketFD, (sockaddr *)&m_sServeraddr, sizeof(m_sServeraddr)) < 0) {
        cout << "connecting error" << endl;
        return -1;
    }
    
    cout << "connected" << endl;
    string input;
    
    cout << "input command:" << endl;
    while(cin >> input) {
        
        Msg msg(0, input);
        int data_length = msg.m_iLength = strlen(input.c_str());

        write(m_iSocketFD, &msg, sizeof(msg));
        
        if(msg.m_eCommand != msg.QUIT && msg.m_eCommand != msg.UNKNOWN)
            write(m_iSocketFD, input.c_str(), strlen(input.c_str()));
        
        m_strData = string();
        
        while(data_length > 0) {
            bzero(m_pcBuffer, sizeof(m_pcBuffer));
            
            int recv_length = read(m_iSocketFD, m_pcBuffer, MAX_LENGTH - 1);
            
            data_length -= recv_length;
            
            if(recv_length <= 0) {
                cout << "disconneted, closing" << endl;
                Close();
                return -1;
            }
            
            m_strData.append(m_pcBuffer);
        }
        
        cout << m_strData << endl;
        cout << "input command:" << endl;
    }
    
    Close();

}

int Client::Close() {
    return close(m_iSocketFD);
}


int main(int argc, char **argv) {
    if(argc != 3) {
        cout << "Usage: filename [ip_address] [port]" << endl;
        
        return -1;
    }

    Client client(argv[1], atoi(argv[2]));
    client.Connect();
    
}
