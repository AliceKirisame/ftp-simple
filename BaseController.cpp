#include "BaseController.h"

BaseController::BaseController(string initDir, int socketFD) : m_phNowDir(initDir), m_iSocketFD(socketFD) ,m_Transer(Transmitter(socketFD)){

    directory_iterator its(initDir);
    
    m_strFileList = string();
    for(auto& it : its) {
        m_vecFiles.push_back(it.path().filename());
        
        m_strFileList.append(it.path().filename());
        m_strFileList.append("\n");
    }

}

BaseController::BaseController(string initDir) : BaseController(initDir, -1){

}

BaseController::~BaseController() {}

int BaseController::setSocketFD(int socketFD) {
    return m_Transer.setSocketFD(socketFD);
}

int BaseController::Exec() {

    switch(m_Msg.m_eCommand) {
        
        case Msg::QUIT:
            
            Quit();
            break;
        
        case Msg::CD:
            
            Cd();
            break;
            
        case Msg::CDUP:
            
            Cdup();
            break;
        
        case Msg::LS:
            
            Ls();
            break;
            
        case Msg::PUT:
            Put();
            break;
            
        case Msg::GET:
            Get();
            break;
            
        default:
            string error_msg = "unknown command";
            
            Msg msg(error_msg.size());
    
            m_Transer.Send(&msg, sizeof(msg));
            m_Transer.Send(error_msg.c_str(), error_msg.size());
            break;
    }

    return 0;
}

int BaseController::Quit() {
    
    m_Transer.setIsConnected(false);
    
    return 0;
}

