#include "ServerController.h"

ServerController::ServerController(string initDir, int socketFD) : Controller(initDir, socketFD) {

    directory_iterator its(initDir);
    
    m_strFileList = string();
    for(auto& it : its) {
        m_vecFiles.push_back(it.path().filename());
        
        m_strFileList.append(it.path().filename());
        m_strFileList.append("\n");
    }

}

ServerController::ServerController(string initDir) : ServerController(initDir, -1){

}

ServerController::ServerController(int socketFD) : ServerController(".", socketFD){

}

int ServerController::Transmit() {
    
    try {
        
        while(m_Transer.getIsConnected()) {

            m_Transer.Receive(&m_Msg, sizeof(m_Msg));
            m_iTargetDataLength = m_Msg.m_iLength;
            
            cout << "command id:" << m_Msg.m_eCommand << endl;
            
            Exec();
            
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


int ServerController::Ls() {
    
    Msg msg(m_strFileList.size());
    
    cout << "return:\n" <<m_strFileList << endl;
    m_Transer.Send(&msg, sizeof(msg));
    m_Transer.Send(m_strFileList.c_str(), m_strFileList.size());

    return 0;
}

int ServerController::Cd() {
    //文件夹检测未做
    string fileName;
    cout << "in Cd" << endl;
    m_Transer.receiveStr(fileName, m_iTargetDataLength);
    
    cout << "cd " << fileName << endl;
    
    m_phNowDir.append(fileName);
    cout << "enter:" << m_phNowDir << endl;
    
    m_vecFiles = vector<string>();
    m_strFileList = string("");
    
    directory_iterator its(m_phNowDir);
    
    for(auto& it : its) {
        m_vecFiles.push_back(it.path().filename());
        
        m_strFileList.append(it.path().filename());
        m_strFileList.append("\n");
        
//         cout << it.path().filename() << endl;
    }
    
//     m_strFileList = string("cd");
    
    Ls();
    
    return 0;
}

int ServerController::Cdup() {
    
    m_phNowDir = m_phNowDir.parent_path();
    cout << "enter " << m_phNowDir << endl;
    m_vecFiles.clear();
    m_strFileList = string("");
    
    
    directory_iterator its(m_phNowDir);
    
    for(auto& it : its) {
        m_vecFiles.push_back(it.path().filename());
        
        m_strFileList.append(it.path().filename());
        m_strFileList.append("\n");
    }
    
    Ls();
    
    return 0;
}

int ServerController::Put() {
    
#ifdef DEBUG
    cout << "data_length:" << m_iTargetDataLength << endl;
#endif
    
    string fileName;
    m_Transer.receiveStr(fileName, m_iTargetDataLength);
    
    
#ifdef DEBUG
    cout << "filename:" << fileName << endl;
#endif
    
    
    path filePath = m_phNowDir;
    filePath.append(fileName);
    
    
#ifdef DEBUG
    cout << "filePath:" << string(filePath) << endl;
#endif    
    
    
    m_Transer.Receive(&m_Msg, sizeof(m_Msg));

    int targetDataLength = m_Msg.m_iLength;
    ofstream targetFileStream(filePath, ios::out|ios::binary|ios::trunc);
    m_Transer.receiveFile(targetFileStream, targetDataLength);
    
    m_Msg.m_iLength = file_size(filePath);
    
    m_Transer.Send(&m_Msg, sizeof(m_Msg));
    
    cout << "Transmited " << targetDataLength << " bytes" << endl;
    
    return 0;
}

int ServerController::Get() {
    
#ifdef DEBUG
    cout << "data_length:" << m_iTargetDataLength << endl;
#endif
    
    
    string fileName;
    m_Transer.receiveStr(fileName, m_iTargetDataLength);
    
    
#ifdef DEBUG
    cout << "filename:" << fileName << endl;
#endif
    
    
    path filePath = m_phNowDir;

    filePath.append(fileName);
    
    
#ifdef DEBUG
    cout << "filePath:" << string(filePath) << endl;
#endif    
    
    
    int targetDataLength = file_size(filePath);
    
    
#ifdef DEBUG
    cout << "targetDataLength:" << targetDataLength << endl;
#endif    
    
    
    ifstream targetFileStream(filePath, ios::in|ios::binary);
    
    Msg msg(targetDataLength);
    
    m_Transer.Send(&msg, sizeof(msg));
    m_Transer.sendFile(targetFileStream, targetDataLength);
    
    cout << "Transmited " << targetDataLength << " bytes" << endl;
    
    return 0;
}

int ServerController::Unknown() {
    
    string errorMsg("Unknown command");
    Msg msg(errorMsg.size());
    
    m_Transer.Send(&msg, sizeof(msg));
    m_Transer.sendStr(errorMsg);
    
    return 0;
}
