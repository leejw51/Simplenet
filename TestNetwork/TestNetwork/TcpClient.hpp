//
//  TcpClient.hpp
//  TestNetwork
//
//  Created by leejw51 on 2017. 8. 29..
//  Copyright © 2017년 Jongwhan Lee. All rights reserved.
//

#ifndef TcpClient_hpp
#define TcpClient_hpp
#include <string>

#include "BasicServer.hpp"
namespace Simplenet {
    class TcpClient:public BasicServer {
    public:
        std::string _ip;
        int _port;
        TcpClient();
        void start(std::string ip, int port);
        void process();
    };
}

#endif /* TcpClient_hpp */
