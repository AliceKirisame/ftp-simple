#include "ClientController.h"

ClientController::ClientController(string initDir, int socketFD) : Controller(initDir, socketFD) {

    directory_iterator its(initDir);
    
    m_strFileList = string();
    for(auto& it : its) {
        m_vecFiles.push_back(it.path().filename());
        
        m_strFileList.append(it.path().filename());
        m_strFileList.append("\n");
    }

}

ClientController::ClientController(string initDir) : ClientController(initDir, -1){

}

ClientController::ClientController(int socketFD) : ClientController(".", socketFD){

}

int ClientController::Transmit() {
    
    try {
        
        cout << "input command:" << endl;
        string input;
        
        while(m_Transer.getIsConnected() && cin >> input) {
            
            m_Msg.setCommmand(m_Msg.getComId(input));
            
            switch(m_Msg.m_eCommand) {
            
                case Msg::CD:
                    
                case Msg::PUT:

                case Msg::GET:
                    
                    m_strTargetData = string("");
                    cin >> m_strTargetData;

                    m_iTargetDataLength = m_strTargetData.size();
                    m_Msg.setDataLength(m_iTargetDataLength);
                    break;
                    
                default:

                    break;
            }
            
            m_Transer.Send(&m_Msg, sizeof(m_Msg));
            Exec();
            
            if(m_Transer.getIsConnected()) cout << "input command:" << endl;
            
        }
    }

    catch(exception e) {
        cout << e.what() << endl;
        close(m_iSocketFD);
    }
    
    cout << "disconnected, closing FD" << endl << endl;
    close(m_iSocketFD);

    return 0;
}


int ClientController::Ls() {
    
    string fileList;
    m_Transer.Receive(&m_Msg, sizeof(m_Msg));
    m_Transer.receiveStr(fileList, m_Msg.m_iLength);
    
#ifdef DEBUG
    cout << endl << "Data.size():should be " << m_Msg.m_iLength << endl;
    cout << "Data.size():" << fileList.size() << endl << endl;
#endif
    
    cout << fileList << endl;
    
    return 0;
}

int ClientController::Cd() {

    m_Transer.sendStr(m_strTargetData);
    
    Ls();
    
    return 0;
}

int ClientController::Cdup() {
    
    Ls();
    
    return 0;
}


int ClientController::Put() {
    
    m_Transer.sendStr(m_strTargetData);
    
    path filePath(".");
    filePath.append(m_strTargetData);
    m_iTargetDataLength = file_size(m_strTargetData);
    
    m_Msg.setDataLength(m_iTargetDataLength);
    
    m_Transer.Send(&m_Msg, sizeof(m_Msg));
    
    ifstream targetFile(m_strTargetData, ios::in|ios::binary);
    m_Transer.sendFile(targetFile, m_Msg.m_iLength);
    
    m_Transer.Receive(&m_Msg, sizeof(m_Msg));
    
    cout << "Transmited " << m_Msg.m_iLength << " bytes" << endl;
    
    return 0;
}

int ClientController::Get() {
    
    m_Transer.sendStr(m_strTargetData);
    
    m_Transer.Receive(&m_Msg, sizeof(m_Msg));
    ofstream targetFile(m_strTargetData, ios::out|ios::binary|ios::trunc);
    m_Transer.receiveFile(targetFile, m_Msg.m_iLength);
    
    cout << "Transmited " << m_Msg.m_iLength << " bytes" << endl;
    
    return 0;
}

int ClientController::Unknown() {
    
    Ls();
    
    return 0;
}
