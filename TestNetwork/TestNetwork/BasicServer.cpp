//
//  BasicServer.cpp
//  TestNetwork
//
//  Created by Jongwhan Lee on 29/08/2017.
//  Copyright © 2017 Jongwhan Lee. All rights reserved.
//

#include "BasicServer.hpp"

namespace Simplenet {
    BasicServer::BasicServer()
    {
        _exit = false;        
    }
    
    void BasicServer::startThread()
    {
        _thread = std::thread(&BasicServer::process, this);
    }
    void BasicServer::stopThread()
    {
        _exit = true;
        _thread.join();
    }
    void BasicServer::stop()
    {
        stopThread();
    }
}
