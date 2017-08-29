//
//  TcpServer.hpp
//  TestNetwork
//
//  Created by Jongwhan Lee on 29/08/2017.
//  Copyright © 2017 Jongwhan Lee. All rights reserved.
//
#ifndef TcpServer_hpp
#define TcpServer_hpp
#include "BasicServer.hpp"
namespace Simplenet {
    class TcpServer:public BasicServer {
    public:
        int _port;
        TcpServer();
        void start(int port);
       
        void process();
    };
}

#endif /* TcpServer_hpp */
