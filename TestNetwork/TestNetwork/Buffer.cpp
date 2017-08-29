//
//  Buffer.cpp
//  serialization, deserialization
//  TestNetwork
//
//  Created by Jongwhan Lee on 29/08/2017.
//  Copyright © 2017 Jongwhan Lee. All rights reserved.
//

#include "Buffer.hpp"
#include <cassert>
using namespace std;
namespace Simplenet {
    void Buffer::putInt(int v)
    {
        char* src = (char*) &v;
        _buffer.append(src, 4);
    }
    int Buffer::getInt(int& index)
    {
        const char* src = _buffer.c_str() + index;
        int ret = -1;
        memcpy(&ret, src, 4);
        index += 4;
        return ret;
    }
    void Buffer::putDouble(double v)
    {
        assert(8 == sizeof(double));
        char* src = (char*) &v;
        _buffer.append(src, 8);
    }
    double Buffer::getDouble(int& index)
    {
        const char* src = _buffer.c_str() + index;
        double ret = -1;
        memcpy(&ret, src, 8);
        index += 8;
        return ret;
    }
    // string
    void Buffer::putString(string v)
    {
        int length = (int)v.length();
        putInt(length);
        const char* src = (const char*) v.c_str();
        _buffer.append(src, length);
    }
    string Buffer::getString(int& index)
    {
        int length = getInt(index);
        const char* src = _buffer.c_str() + index;
        string ret;
        ret.resize(length);
        memcpy((char*)ret.data(), src, length);
        index += length;
        return ret;
    }
}
