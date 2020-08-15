#include "controller.h"

Controller::Controller(string initDir, int socketFD) : m_phNowDir(initDir), m_iSocketFD(socketFD) ,m_Transer(Transmitter(socketFD)){

    directory_iterator its(initDir);
    
    m_strFileList = string();
    for(auto& it : its) {
        m_vecFiles.push_back(it.path().filename());
        
        m_strFileList.append(it.path().filename());
        m_strFileList.append("\n");
    }

}

Controller::Controller(string initDir) : Controller(initDir, -1){

}

Controller::~Controller() {}

int Controller::setSocketFD(int socketFD) {
    return m_Transer.setSocketFD(socketFD);
}

int Controller::Exec() {
    Msg msg;
    
    try {

        while(m_Transer.getIsConnected()) {

            if(m_Transer.Receive(&msg, sizeof(msg)) < 0) break;
            
            cout << "command id:" << msg.m_eCommand << endl;

            switch(msg.m_eCommand) {
                
                case Msg::QUIT:
                    
                    Quit();
                    break;
                
                case Msg::CD:
                    
                    Cd(msg.m_iLength);
                    break;
                    
                case Msg::CDUP:
                    
                    Cdup();
                    break;
                
                case Msg::LS:
                    
                    Ls();
                    break;
                    
                case Msg::PUT:
                    Put(msg.m_iLength);
                    break;
                    
                case Msg::GET:
                    Get(msg.m_iLength);
                    break;
                    
                default:
                    string error_msg = "unknown command";
                    
                    Msg msg(error_msg.size());
            
                    m_Transer.Send(&msg, sizeof(msg));
                    m_Transer.Send(error_msg.c_str(), error_msg.size());
                    break;
            }
        }
    }
    catch(exception e) {
        cout << e.what() << endl;
        return -1;
    }

    return 0;
}

int Controller::Quit() {
    
    m_Transer.setIsConnected(false);
    
    return 0;
}

int Controller::Ls() {
    
    Msg msg(m_strFileList.size());
    
    cout << "return:\n" <<m_strFileList << endl;
    m_Transer.Send(&msg, sizeof(msg));
    m_Transer.Send(m_strFileList.c_str(), m_strFileList.size());

    return 0;
}

int Controller::Cd(int data_length) {
    //文件夹检测未做
    string filename;
    cout << "in Cd" << endl;
    m_Transer.receiveStr(filename, data_length);
    
    cout << "cd " << filename << endl;
    
    m_phNowDir.append(filename);
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
    cout << "return:\n" <<m_strFileList << endl;
    Msg msg(m_strFileList.size());
    
    m_Transer.Send(&msg, sizeof(msg));
    m_Transer.Send(m_strFileList.c_str(), m_strFileList.size());
    
    return 0;
}

int Controller::Cdup() {
    
    m_phNowDir = m_phNowDir.parent_path();
    cout << "enter " << m_phNowDir << endl;
    m_vecFiles.clear();
    m_strFileList = string("");
    
    
    directory_iterator its(m_phNowDir);
    
    for(auto& it : its) {
        m_vecFiles.push_back(it.path().filename());
        
        m_strFileList.append(it.path().filename());
//         m_strFileList.append("?");
        m_strFileList.append("\n");
    }
    
//     m_strFileList = string("cdup");
    Msg msg(m_strFileList.size());
    
    cout << "return:\n" <<m_strFileList << endl;
    m_Transer.Send(&msg, sizeof(msg));
    m_Transer.Send(m_strFileList.c_str(), m_strFileList.size());
    
    return 0;
}

int Controller::Put(int data_length) {
    
#ifdef DEBUG
    cout << "data_length:" << data_length << endl;
#endif
    
    
    string filename;
    m_Transer.receiveStr(filename, data_length);
    
    
#ifdef DEBUG
    cout << "filename:" << filename << endl;
#endif
    
    
    path filePath = m_phNowDir;
    filePath.append(filename);
    
    
#ifdef DEBUG
    cout << "filePath:" << string(filePath) << endl;
#endif    
    
    
    Msg msg(0);
    m_Transer.Receive(&msg, sizeof(msg));

    int targetFileLength = msg.m_iLength;
    ofstream targetFileStream(filePath, ios::out|ios::binary|ios::trunc);
    m_Transer.receiveFile(targetFileStream, targetFileLength);
    
    msg.m_iLength = file_size(filePath);
    
    m_Transer.Send(&msg, sizeof(msg));
    
    return 0;
}

int Controller::Get(int data_length) {

#ifdef DEBUG
    cout << "data_length:" << data_length << endl;
#endif
    string filename;
    m_Transer.receiveStr(filename, data_length);
#ifdef DEBUG
    cout << "filename:" << filename << endl;
#endif
    path filePath = m_phNowDir;

    filePath.append(filename);
#ifdef DEBUG
    cout << "filePath:" << string(filePath) << endl;
#endif    
    
    int targetFileLength = file_size(filePath);
    ifstream targetFileStream(filePath, ios::in|ios::binary);

    Msg msg(targetFileLength);
    
    m_Transer.Send(&msg, sizeof(msg));
    m_Transer.sendFile(targetFileStream, targetFileLength);
    
    return 0;
}
