#include "Controller.h"

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

Controller::Controller(int socketFD) : Controller(".", socketFD){

}

Controller::~Controller() {}

int Controller::setSocketFD(int socketFD) {
    return m_Transer.setSocketFD(socketFD);
}

int Controller::Exec() {

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
            Unknown();
            break;
    }

    return 0;
}

int Controller::Quit() {
    
    m_Transer.setIsConnected(false);
    
    return 0;
}

