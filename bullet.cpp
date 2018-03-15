// UTF-8 BOM

#include "allinclusions.hpp"


Bullet::Bullet()
{}

uint8_t Bullet::GetDamage() const noexcept
{
    return m_damage;
}

void Bullet::SetDamage(uint8_t damage) noexcept
{
    m_damage = damage;
}
