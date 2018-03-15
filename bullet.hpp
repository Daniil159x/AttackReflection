// UTF-8 BOM

#ifndef BULLET_HPP
#define BULLET_HPP

#include "allinclusions.hpp"

class Bullet : public Disappearing
{
public:
    Bullet();
    Bullet(const sf::Texture& texture, const sf::IntRect& rectangle, uint8_t dmg, uint8_t lvls = 1);

    // TODO: добавить физику

    uint8_t GetDamage() const noexcept;
    void SetDamage(uint8_t damage) noexcept;

private:
    uint8_t m_damage;
};

#endif // BULLET_HPP