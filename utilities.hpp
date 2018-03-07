// UTF-8 BOM

#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include "allinclusions.hpp"

constexpr int gcd(int f, int s){
    BOOST_ASSERT(f > 0 && s > 0);

    while(f != s){
        if(f > s){
            f -= s;
        }
        else {
            s -= f;
        }
    }
    return f;
}

constexpr int lcm(int f, int s){
    BOOST_ASSERT(f > 0 && s > 0);

    return (f * s) / gcd(f, s);
}


#endif // UTILITIES_HPP
