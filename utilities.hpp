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

inline float CalculateRotate(const sf::Vector2f &from, const sf::Vector2f &to)
{
    return std::atan2(to.y - from.y, to.x - from.x) * 180 / static_cast<float>(M_PI);
}

class TextureHelper;
namespace Collision {
    bool PixelPerfectTest(const sf::Sprite& obj_1, const sf::Sprite& obj_2, sf::Uint8 AlphaLimit = 127);
}

#endif // UTILITIES_HPP
