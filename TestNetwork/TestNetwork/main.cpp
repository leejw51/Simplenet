//
//  main.cpp
//  TestNetwork
//
//  Created by Jongwhan Lee on 29/08/2017.
//  Copyright © 2017 Jongwhan Lee. All rights reserved.
//

#include <iostream>
#include "Buffer.hpp"
using namespace Simplenet;
using namespace std;
int main(int argc, const char * argv[]) {
    Buffer b;
    b.putInt(200);
    b.putString("hello");
    b.putDouble(5.2);
    cout<<"Size="<<b._buffer.size()<<endl;
    int index = 0;
    Buffer c = b;
    int c1 = c.getInt(index);
    string c12;
    c12 = c.getString(index);
    double c2 = c.getDouble(index);
    cout<< c1 <<endl;
    cout<< c12 << endl;
    cout<< c2 <<endl;
    return 0;
}
