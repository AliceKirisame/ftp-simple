#include "transmitter.h"

Transmitter::Transmitter(int socketFD):m_iSocketFD(socketFD), m_bIsConnected(true) {
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

int Transmitter::sendStr(string &sendStr) {
    
    int data_length = sendStr.size();
    int written_length = 0;
    
    while(data_length != 0) {
        
        int send_length = write(m_iSocketFD, sendStr.c_str() + written_length, data_length);
        
        if(send_length <= 0) {
            
            return errorExit("SendStr error");

        }
        
        written_length += send_length;
        data_length -= send_length;
    }
    
    return 0;
}

int Transmitter::receiveStr(string &recvStr, int data_length) {
    
    
#ifdef DEBUG    
    cout <<  endl << "in receiveStr" << endl;
    cout << "data_length " << data_length << endl;
#endif
    
    
    while(data_length != 0) {
                    
        bzero(m_pcBuffer, MAX_LENGTH);
        int recv_length = read(m_iSocketFD, m_pcBuffer, data_length);
        
        
#ifdef DEBUG        
        cout << endl << "recv_length " << recv_length << endl;
        cout << "m_pcBuffer " << strlen(m_pcBuffer) << endl << endl;
#endif
        
        
        if(recv_length <= 0) {
            
            return errorExit("ReceiveStr error");
            
        }
    
        recvStr.append(m_pcBuffer);
        
        data_length -= recv_length;
        
    }
    
    
#ifdef DEBUG    
    cout << endl << "recvStr length " << recvStr.size() << endl;
    cout << "out receiveStr" << endl << endl;
#endif
    
    
    return 0;
}

int Transmitter::Send(const void * pData, int data_length) {
    
    
#ifdef DEBUG    
    cout << endl << "in Send" << endl;
    cout << "data_length " << data_length << endl << endl;
#endif
    
    
    unsigned char *pSendData = (unsigned char *)pData;
    
    int written_length = 0;
    
    while(data_length != 0) {
        int send_length = write(m_iSocketFD, pSendData + written_length, data_length);
        
        if(send_length <= 0) {
            
            return errorExit("Sending error");

        }
        
        written_length += send_length;
        data_length -= send_length;
        
        
#ifdef DEBUG        
    cout << endl << "written_length " << written_length  << endl << endl;
#endif
    }
#ifdef DEBUG    
    cout << "out Send" << endl << endl;
#endif
    
    
    return 0;
}

void * Transmitter::Receive(int data_length) {
    
    unsigned char * pRecvData = new unsigned char[data_length];
    int recved_length = 0;
    
    while(data_length != 0) {
                    
        int recv_length = read(m_iSocketFD, pRecvData + recved_length, data_length);
        
        if(recv_length <= 0) {
            
            errorExit("Receiving error");
            delete[] pRecvData;
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
            
            return errorExit("Receiving error");
            
        }
        
        recved_length += recv_length;
        data_length -= recv_length;
    }
    
    return 0;
}

int Transmitter::sendFile(ifstream &targetFileStream, int data_length) {
    
    while(targetFileStream.good() && data_length != 0) {
        
        bzero(m_pcBuffer, MAX_LENGTH);
        targetFileStream.read(m_pcBuffer, MAX_LENGTH);
        int send_length = write(m_iSocketFD, m_pcBuffer, targetFileStream.gcount());
        
        
#ifdef DEBUG
        cout << endl << "send_length " << send_length << endl << endl;
#endif  
        
        
        if(send_length <= 0) {
            
            return errorExit("SendFile error");

        }
        
        data_length -= targetFileStream.gcount();
    }
    
    return 0;
}

int Transmitter::receiveFile(ofstream &targetFileStream, int data_length) {
    
    while(targetFileStream.good() && data_length != 0) {
        
        bzero(m_pcBuffer, MAX_LENGTH);
        int recv_length = read(m_iSocketFD, m_pcBuffer, MAX_LENGTH);
        targetFileStream.write(m_pcBuffer, recv_length);
   
        
#ifdef DEBUG
        cout << endl << "recv_length " << recv_length << endl << endl;
#endif        

        
        if(recv_length <= 0) {
            
            return errorExit("ReceiveFile error");

        }
        
        data_length -= recv_length;
        
    }
    
    return 0;
}

int Transmitter::errorExit(string errorMsg) {
    m_bIsConnected = false;
    cout << errorMsg << endl;
            
    return -1;
}
