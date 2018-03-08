// UTF-8 BOM

#ifndef BULLET_HPP
#define BULLET_HPP

#include "allinclusions.hpp"

class Bullet : public Disappearing
{
public:
    Bullet(const sf::Texture& texture, const sf::IntRect& rectangle, uint8_t dmg, uint8_t lvls = 1);

    inline static float TargetRotate(sf::Vector2f const &from, sf::Vector2f const &to);

    // TODO: добавить физику

    uint8_t GetDamage() const noexcept;
    void SetDamage(uint8_t damage) noexcept;

private:
    uint8_t m_damage;
};

#endif // BULLET_HPP