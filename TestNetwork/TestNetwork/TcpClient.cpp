//
//  TcpClient.cpp
//  TestNetwork
//
//  Created by leejw51 on 2017. 8. 29..
//  Copyright © 2017년 Jongwhan Lee. All rights reserved.
//

#include "TcpClient.hpp"
#include <netdb.h>
#include <cassert>
namespace Simplenet {
    TcpClient::TcpClient()
    {
        
    }
    
    void TcpClient::start(std::string ip, int port)
    {
        _ip = ip;
        _port = port;
        BasicServer::startThread();
    }
    void TcpClient::process()
    {
        int s = socket(PF_INET6, SOCK_STREAM, IPPROTO_TCP);
        int r = -1;
        struct hostent* hp = gethostbyname2(_ip.c_str(), AF_INET6);
        // set inet6
        struct sockaddr_in6 sin;
        memset(&sin, 0, sizeof(sin));
        sin.sin6_len = sizeof(sin);
        memcpy((char *)&sin.sin6_addr, hp->h_addr, hp->h_length);
        sin.sin6_family = hp->h_addrtype ; // or AF_INET6 (address family)
        sin.sin6_port = htons(_port);
        r = connect(s, (struct sockaddr *)&sin, sizeof(sin));
        assert(0<= r);
        while(!_exit) {
            printf("TcpClient\n");
            std::this_thread::sleep_for(std::chrono::seconds(1));
            char buf[300];
            memset(buf, 0, sizeof(buf));
            r = (int)recv(s, buf, 300, 0);
            if (r>0) {
            printf("Receive %d Bytes = %s\n", r,buf);
            }
        }
    }
}
