#include "transmitter.h"
#include "msg.h"

bool Transmitter::m_bIsConnected = true;

Transmitter::Transmitter(int socketFD):m_iSocketFD(socketFD) {
    m_pcBuffer = new char[MAX_LENGTH];

}

Transmitter::Transmitter():Transmitter(-1) {

}

Transmitter::~Transmitter() {

    delete []m_pcBuffer;
}

bool Transmitter::getIsConnected() {
    return m_bIsConnected;
}

bool Transmitter::setIsConnected(bool b) {
    return m_bIsConnected = b;
}

int Transmitter::setSocketFD(int socketFD) {
    return m_iSocketFD = socketFD;
}

int Transmitter::sendStr(string & sendStr) {
    
    int data_length = sendStr.size();
    int written_length = 0;
    
    while(data_length != written_length) {
        
        int write_length = write(m_iSocketFD, sendStr.c_str() + written_length, data_length - written_length);
        
        if(write_length <= 0) {
            
            m_bIsConnected = false;
            cout << "Sending error" << endl;
            return -1;
        }
        
        written_length += write_length;
    }
    
    return 0;
}

int Transmitter::receiveStr(string & recvStr, int data_length) {
    
#ifdef DEBUG    
    cout << "in receiveStr" << endl;
    cout << "data_length " << data_length << endl;
    cout << "recvStr length " << recvStr.size() << endl;
#endif
    
    while(data_length != 0) {
                    
        bzero(m_pcBuffer, MAX_LENGTH);
        int recv_length = read(m_iSocketFD, m_pcBuffer, MAX_LENGTH);
#ifdef DEBUG        
        cout << "recv_length " << recv_length << endl;
        cout << "m_pcBuffer " << strlen(m_pcBuffer) << endl;
#endif
        if(recv_length <= 0) {
            
            m_bIsConnected = false;
            cout << "Receiving error" << endl;
            
            return -1;
        }
    
        recvStr.append(m_pcBuffer);
        
        data_length -= recv_length;
        
    }
#ifdef DEBUG    
    cout << "recvStr length " << recvStr.size() << endl;
    cout << "out receiveStr" << endl;
#endif
    return 0;
}

int Transmitter::Send(const void * pData, int data_length) {
#ifdef DEBUG    
    cout << "in Send" << endl;
#endif
    unsigned char *pSendData = (unsigned char *)pData;
    
    int written_length = 0;
    
    while(data_length != written_length) {
        int write_length = write(m_iSocketFD, pSendData + written_length, data_length - written_length);
        
        if(write_length <= 0) {
            
            m_bIsConnected = false;
            cout << "Sending error" << endl;
            
            return -1;
        }
        
        written_length += write_length;
#ifdef DEBUG        
        cout << "written_length " << written_length << " data_length " << data_length << endl;
#endif
    }
#ifdef DEBUG    
    cout << "out Send" << endl;
#endif
    return 0;
}

void * Transmitter::Receive(int data_length) {
    
    unsigned char * pRecvData = new unsigned char[data_length];
    int recved_length = 0;
    
    while(data_length != 0) {
                    
        int recv_length = read(m_iSocketFD, pRecvData + recved_length, data_length);
        
        if(recv_length <= 0) {
            
            m_bIsConnected = false;
            cout << "Receiving error" << endl;
            
            return NULL;
        }
        
        recved_length += recv_length;
        data_length -= recv_length;
    }
    
    return pRecvData;
}

int Transmitter::Receive(void * pData, int data_length) {
    
    unsigned char* pRecvData = (unsigned char *)pData;
    
    int recved_length = 0;
    
    while(data_length != 0) {
                    
        int recv_length = read(m_iSocketFD, pRecvData + recved_length, data_length);
        
        if(recv_length <= 0) {
            
            m_bIsConnected = false;
            cout << "Receiving error" << endl;
            
            return -1;
        }
        
        recved_length += recv_length;
        data_length -= recv_length;
    }
    
    return 0;
}
