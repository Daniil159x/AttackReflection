// UTF-8 BOM

#include "allinclusions.hpp"


float Bullet::TargetRotate(const sf::Vector2f &from, const sf::Vector2f &to)
{
    return std::atan2(to.y - from.y, to.x - from.x) * 180 / static_cast<float>(M_PI);
}

uint8_t Bullet::GetDamage() const noexcept
{
    return m_damage;
}

void Bullet::SetDamage(uint8_t damage) noexcept
{
    m_damage = damage;
}
