//
//  TcpServer.cpp
//  TestNetwork
//
//  Created by Jongwhan Lee on 29/08/2017.
//  Copyright © 2017 Jongwhan Lee. All rights reserved.
//

#include "TcpServer.hpp"
#include <unistd.h>
#include <iostream>
#include <cassert>
#include <chrono>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
namespace Simplenet {
    void TcpAcceptMessage::process(TcpServer&p)
    {
        assert(0<= _socket);
        p.doAddSession(_socket);
    }
    TcpServer::TcpServer()
    {
        _listenSocket = -1;
    }
    
    void TcpServer::stop()
    {
        for (auto session: this->_sessions) {
            session->_exit = true;
        }
        _exit = true;
        if (_listenSocket>0) {
            close(_listenSocket);
            _listenSocket = -1;
        }
        
        // join
        _acceptThread.join();
        for (auto session: this->_sessions) {
            session->finalize();
        }
        
        BasicServer::stop();
        
    }
    void TcpServer::processAccept()
    {
        while(!_exit) {
        std::cout<<"Processing Accept"<<std::endl;
        struct sockaddr peer;
        socklen_t peerLength;
        int connectfd = accept(_listenSocket,&peer, &peerLength);
        if (connectfd>=0) {
            printf("Accepted=%d\n", connectfd);            
            addSession(connectfd);
        }
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
    void TcpServer::checkSessions()
    {
        auto tmp = _sessions;
        for (auto session: tmp) {
            if (!session->_active) {
                removeSession(session);
            }
        }
    }
    
    void TcpServer::process()
    {
        int s = socket(PF_INET6, SOCK_STREAM, IPPROTO_TCP);
        _listenSocket = s;
        _acceptThread = std::thread(&TcpServer::processAccept, this);
        int r = -1;
        int enable = 1;
        // reuse address
        r=setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) ;
        assert(0<=r);
        // set inet6
        struct sockaddr_in6 sin;
        memset(&sin, 0, sizeof(sin));
        sin.sin6_len = sizeof(sin);
        sin.sin6_family = AF_INET6; // or AF_INET6 (address family)
        sin.sin6_port = htons(_port);
        sin.sin6_addr = in6addr_any;
        // bind
        r = bind(s, (struct sockaddr *)&sin, sizeof(sin));
        assert(0<=r);
        // listen
        r = listen(s, 5);
        assert(0<=r);
        std::chrono::seconds dura(1);
        while(!_exit) {
            //std::this_thread::sleep_for(std::chrono::seconds(1));
            MessageShared message;
            bool re = _queue.pop(message);
            if (re) {
                assert(message.get()!=nullptr);
                message->process(*this);
            }
            checkSessions();
        }
    }
   
    void TcpServer::start(int port)
    {
        printf("Port=%d\n", port);
        _port = port;
        BasicServer::startThread();
    }
    
    void TcpServer::addSession(int socket)
    {
        TcpAcceptMessage* m = new TcpAcceptMessage();
        m->_socket = socket;
        MessageShared m2(m);
        _queue.push(m2);
    }
    void TcpServer::doAddSession(int socket)
    {
        auto newone = TcpSessionShared(new TcpSession());
        newone->initialize(socket);
        this->_sessions.push_back(newone);
    }
    
    void TcpServer::removeSession(TcpSessionShared t)
    {
        t->finalize();
        this->_sessions.remove(t);
    }
}
