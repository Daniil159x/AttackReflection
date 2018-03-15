// UTF-8 BOM

#include "allinclusions.hpp"


Mob::Mob()
{}

Mob::Mob(const sf::Texture &texture, const sf::IntRect &rectangle, int8_t hp, uint8_t lvls)
    : Disappearing (texture, rectangle, lvls), m_hp(hp)
{}

void Mob::SetHP(int8_t hp) noexcept
{
    m_hp = hp;
}

int8_t Mob::GetHP() const noexcept
{
    return m_hp;
}

bool Mob::Damage(int8_t d) noexcept
{
    if(Alive() && (m_hp >= INT8_MIN + d))
    {
        m_hp -= d;
        return m_hp > 0;
    }
    return false;
}

bool Mob::Alive() const noexcept
{
    return m_hp > 0;
}
