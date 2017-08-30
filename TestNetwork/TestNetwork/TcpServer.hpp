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
#include "TcpSession.hpp"
#include "Queue.hpp"
#include <list>
#include <map>
#include <mutex>
#include <memory>
namespace Simplenet {
    class TcpServer;
    class TcpServerMessage {
    public:
        TcpServerMessage()
        {
        }
        virtual void process(TcpServer&){}
    };
    typedef std::shared_ptr<TcpServerMessage> MessageShared;
    class TcpAcceptMessage: public TcpServerMessage {
    public:
        TcpAcceptMessage()
        {
            _socket = -1;
        }
        int _socket;
        void process(TcpServer&);
    };
    class TcpServer:public BasicServer {
    public:
        // enqueue, dequeue
        Queue<MessageShared> _queue;
        std::mutex _lock;
        std::list<TcpSessionShared> _sessions;
        std::thread _acceptThread;
        int _port;
        int _listenSocket;
        TcpServer();
        void start(int port);
        void stop();
        void process();
        void processAccept();
        void addSession(int socket);
        void doAddSession(int socket);
        void removeSession(TcpSessionShared t);
        void checkSessions();
    };
}

#endif /* TcpServer_hpp */
