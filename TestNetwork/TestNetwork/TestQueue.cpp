//
//  TestQueue.cpp
//  TestNetwork
//
//  Created by 이종환 on 30/08/2017.
//  Copyright © 2017 Jongwhan Lee. All rights reserved.
//

#include "TestQueue.hpp"
#include "Queue.hpp"
#include <thread>
#include <chrono>
#include <string>
#include <iostream>
using namespace Simplenet;
using namespace std;
void proudcerThread(Queue<int>* q, bool* quit, int w)
{
    int v = 200+w*10;
    while(!*quit) {
        printf("%d Producing..%d\n",w,v);
        q->push(v);
        this_thread::sleep_for(chrono::milliseconds(2000));
        
        v += 5;
    }
}

void consumerThread(Queue<int>* q, bool* quit, int w)
{
    while(!*quit) {
        //printf("%d Consuming..\n",w);
        int output = -1;
        bool re = q->pop(output);
        if (!re)
            continue;
        printf("%d Received=%d\n", w, output);
    }
}

void testQueue()
{
    bool quit = false;
    Queue<int> a;
    thread p(proudcerThread,&a,&quit,101);
    thread p2(proudcerThread,&a,&quit,102);
    thread c(consumerThread,&a,&quit,301);
    thread c2(consumerThread,&a,&quit,302);
    
    while(true) {
        string k;
        printf("q. exit\n");
        cin>>k;
        if ("q"==k) {
            quit = true;
            a.quit();
            break;
        }
    }
    p.join();
    c.join();
    p2.join();
    c2.join();
}

