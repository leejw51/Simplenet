//
//  TcpSession.hpp
//  TestNetwork
//
//  Created by leejw51 on 2017. 8. 30..
//  Copyright © 2017년 Jongwhan Lee. All rights reserved.
//

#ifndef TcpSession_hpp
#define TcpSession_hpp

#include <stdio.h>
#include <memory>
#include <thread>
namespace Simplenet {
    class TcpSession {
    public:
        bool _active;
        bool _exit;
        std::thread _receiveThread;
        std::thread _sendThread;
        int _socket;
        TcpSession();
        void initialize(int socket);
        void finalize();
        void processSend();
        void processReceive();
    };
    typedef std::shared_ptr<TcpSession> TcpSessionShared;
}

#endif /* TcpSession_hpp */
