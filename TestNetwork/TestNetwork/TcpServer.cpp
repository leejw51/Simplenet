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


namespace Simplenet {
    TcpServer::TcpServer()
    {        
    }
    
    void TcpServer::process()
    {
        int s = socket(PF_INET6, SOCK_STREAM, IPPROTO_TCP);
        
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
            std::cout<<"Processinig"<<std::endl;
            //std::this_thread::sleep_for(dura);
            struct sockaddr peer;
            int connectfd = accept( s,NULL, NULL);
            printf("Accepted=%d\n", connectfd);
            send(connectfd, "hello", 5, 1);
            
        }
    }
   
    void TcpServer::start(int port)
    {
        _port = port;
        BasicServer::startThread();
    }
    void TcpServer::stop()
    {
        BasicServer::stopThread();
    }
}
