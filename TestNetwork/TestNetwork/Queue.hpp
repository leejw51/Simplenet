//
//  Queue.hpp
//  TestNetwork
//
//  Created by leejw51 on 2017. 8. 30..
//  Copyright © 2017년 Jongwhan Lee. All rights reserved.
//

#ifndef Queue_hpp
#define Queue_hpp

#include <stdio.h>
#include <list>
#include <mutex>
#include <queue>
#include <chrono>
namespace Simplenet {
    template <class T>
    class Queue {
    public:
        std::mutex mx;
        std::condition_variable cv;
        std::queue<T> _nodes;
        bool _exit;
        Queue()
        {
            _exit = false;
        }
        
        void quit()
        {
            _exit = true;
            // to thread exit faster
            cv.notify_all();
        }
        
        void push(T t)
        {
            std::unique_lock<std::mutex> lk(mx);
            _nodes.push(t);
            lk.unlock();
            cv.notify_one();
        }
        
        bool pop(T& output)
        {
            std::unique_lock<std::mutex> lk(mx);
            cv.wait_for(lk, std::chrono::milliseconds(1000),[&]{
                return _exit || !_nodes.empty();
            });
            if (_nodes.size()>0) {
                auto ret = _nodes.front();
                _nodes.pop();
                output = ret;
                return true;
            }
            else {
                return false;
            }
        }
    };
}
#endif /* Queue_hpp */
