//
//  Buffer.hpp
//  TestNetwork
//
//  Created by Jongwhan Lee on 29/08/2017.
//  Copyright © 2017 Jongwhan Lee. All rights reserved.
//

#ifndef Buffer_hpp
#define Buffer_hpp

#include <string>
namespace Simplenet {
    class Buffer {
    public:
        std::string _buffer;
        // integer
        void putInt(int v);
        int getInt(int& index);
        // double
        void putDouble(double v);
        double getDouble(int& index);
        // string
        void putString(std::string v);
        std::string getString(int& index);
    };
}

#endif /* Buffer_hpp */
