#include "transmitter.h"
#include "msg.h"

Transmitter::Transmitter(int socketFD):m_bIsConnected(true), m_iSocketFD(socketFD) {
    m_pcBuffer = new char[MAX_LENGTH];
}

Transmitter::~Transmitter() {
    delete []m_pcBuffer;
}

bool Transmitter::getIsConnected() {
    return m_bIsConnected;
}

int Transmitter::sendStr(string & sendStr) {
    
    int data_length = sendStr.size();
    int written_length = 0;
    
    while(data_length != written_length) {
        int write_length = write(m_iSocketFD, sendStr.c_str() + written_length, data_length - written_length);
        
        if(write_length <= 0) {
            
            m_bIsConnected = false;
            
            return -1;
        }
        
        written_length += write_length;
    }
    
    return 0;
}

int Transmitter::receiveStr(string & recvStr, int data_length) {
    
    while(data_length != 0) {
                    
        bzero(m_pcBuffer, sizeof(m_pcBuffer));
        int recv_length = read(m_iSocketFD, m_pcBuffer, MAX_LENGTH - 1);
        
        if(recv_length <= 0) {
            m_bIsConnected = false;
            cout << "disconneted. closing" << endl;
            
            return -1;
        }
    
        recvStr.append(m_pcBuffer);
        
        data_length -= recv_length;
    }
}

int Transmitter::Send(const void * pData, int data_length) {
    
    unsigned char *pSendData = (unsigned char *)pData;
    
    int written_length = 0;
    
    while(data_length != written_length) {
        int write_length = write(m_iSocketFD, pSendData + written_length, data_length - written_length);
        
        if(write_length <= 0) {
            
            m_bIsConnected = false;
            
            return -1;
        }
        
        written_length += write_length;
    }
    
    return 0;
}

void * Transmitter::Receive(int data_length) {
    
    unsigned char * pRecvData = new unsigned char[data_length];
    int recved_length = 0;
    
    while(data_length != 0) {
                    
        int recv_length = read(m_iSocketFD, pRecvData + recved_length, data_length - recved_length);
        
        if(recv_length <= 0) {
            
            m_bIsConnected = false;
            cout << "disconneted. closing" << endl;
            
            return NULL;
        }
        
        data_length -= recv_length;
    }
    
    return pRecvData;
}

int Transmitter::Receive(void * pData, int data_length) {
    
    unsigned char* pRecvData = (unsigned char *)pData;
    
    int recved_length = 0;
    
    while(data_length != 0) {
                    
        int recv_length = read(m_iSocketFD, pRecvData + recved_length, data_length - recved_length);
        
        if(recv_length <= 0) {
            
            m_bIsConnected = false;
            cout << "disconneted. closing" << endl;
            
            return -1;
        }
        
        data_length -= recv_length;
    }
    
    return 0;
}
