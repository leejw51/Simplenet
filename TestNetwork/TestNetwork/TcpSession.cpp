//
//  TcpSession.cpp
//  TestNetwork
//
//  Created by leejw51 on 2017. 8. 30..
//  Copyright © 2017년 Jongwhan Lee. All rights reserved.
//

#include "TcpSession.hpp"
#include <string>
#include <chrono>
#include <thread>
#include <unistd.h>
#include <sys/socket.h>
namespace Simplenet {
    TcpSession::TcpSession()
    {
        _exit = false;
        _active = true;
        _socket = -1;
    }
    
    void TcpSession::initialize(int socket)
    {
         _socket = socket;
        _sendThread = std::thread(&TcpSession::processSend, this);
        _receiveThread = std::thread(&TcpSession::processReceive, this);
    }
    
    void TcpSession::finalize()
    {
        printf("Session Destroy=%d\n", _socket);
        _exit = true;
        _sendThread.join();
        _receiveThread.join();
    }
    
    void TcpSession::processSend()
    {
        while(!_exit) {
            std::this_thread::sleep_for(std::chrono::seconds(2));
            std::string buf = "hello world!\n";
            int w =(int) send(_socket, buf.c_str(), buf.size(),0 );
            printf("Written=%d\n", w);
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    }
    
    void TcpSession::processReceive()
    {
        while(!_exit) {
            char buf[300];
            memset(buf, 0, sizeof(buf));
            int r = (int)recv(_socket, buf, 300, 0);
            if (r>0) {
                printf("Receive %d Bytes = %s\n", r,buf);
            }
            else if (0==r) {
                printf("Gracefully Closed\n");
                this->_exit = true;
                this->_active = false;
            }
        }
        close(_socket);
    }
}
