#include "ClientController.h"

ClientController::ClientController(string initDir, int socketFD) : BaseController(initDir, socketFD) {

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

int ClientController::Transmit() {

    try {
        string input;
        
        while(m_Transer.getIsConnected() && cin >> input) {
            
            switch(m_Msg.getComId(input)) {
            
                case Msg::CD:
                    
                case Msg::PUT:

                case Msg::GET:
                    
                    cin >> m_strTargetFileName;
                    m_iTargetDataLength = m_strTargetFileName.size();
                    break;
                    
                default:

                    break;
            }
            
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


int ClientController::Ls() {
    return 0;
}

int ClientController::Cd() {
    return 0;
}

int ClientController::Cdup() {
    return 0;
}

int ClientController::Put() {
    return 0;
}

int ClientController::Get() {
    return 0;
}
