// UTF-8 BOM

#include "allinclusions.hpp"


Bullet::Bullet(const sf::Texture &texture, const sf::IntRect &rectangle, uint8_t dmg, uint8_t lvls)
    : Disappearing(lvls), sf::Sprite(texture, rectangle), m_damage(dmg)
{}

uint8_t Bullet::GetDamage() const noexcept
{
    return m_damage;
}

void Bullet::SetDamage(uint8_t damage) noexcept
{
    m_damage = damage;
}

void Bullet::ApplyAlpha_(uint8_t alpha) noexcept
{
    auto c = getColor();
    c.a = alpha;
    this->setColor(c);
}
