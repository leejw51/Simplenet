//
//  BasicServer.hpp
//  TestNetwork
//
//  Created by Jongwhan Lee on 29/08/2017.
//  Copyright © 2017 Jongwhan Lee. All rights reserved.
//

#ifndef BasicServer_hpp
#define BasicServer_hpp
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>
#include <stdio.h>
#include "Queue.hpp"
namespace Simplenet {
    class BasicServer;
    class BasicServerMessage {
    public:
        BasicServerMessage()
        {
        }
        virtual void process(BasicServer*){}
    };
    typedef std::shared_ptr<BasicServerMessage> MessageShared;
    class BasicServer {
    public:
        std::mutex _lock;
        bool _exit;
        std::thread _thread;
        // enqueue, dequeue
        Queue<MessageShared> _queue;
        BasicServer();
        virtual void process()=0;
        virtual void startThread();
        virtual void stopThread();
        virtual void stop();
    };
}

#endif /* BasicServer_hpp */
