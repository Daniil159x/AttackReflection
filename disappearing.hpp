// UTF-8 BOM

#ifndef DISAPPEARING_HPP
#define DISAPPEARING_HPP

#include "allinclusions.hpp"

class Disappearing : public sf::Sprite
{
public:
    Disappearing(const sf::Texture& texture, const sf::IntRect& rectangle, uint8_t lvls = 1);

    inline uint8_t GetLvls() const noexcept;
    inline void SetLvls(uint8_t lvls = 1) noexcept;

    bool NextLevel();

private:
    uint8_t m_lvls;
};

#endif // DISAPPEARING_HPP