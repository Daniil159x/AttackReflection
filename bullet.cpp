// UTF-8 BOM

#include "allinclusions.hpp"


Bullet::Bullet(const sf::Texture &texture, const sf::IntRect &rectangle, uint8_t dmg, uint8_t lvls)
    : Disappearing(lvls), sf::Sprite(texture, rectangle), m_damage(dmg)
{}

void Bullet::Tick(float dx) noexcept
{
    auto dy = std::tan(this->getRotation() * static_cast<float>(M_PI) / 180) * dx;
    this->move(dx, dy);

    // TODO: физика

    /*
    auto r = this->getRotation();

    sy = 0;

    auto x = sx * m_tick * std::cos(r);
    const float g = 1;

    auto s_sqr = sx*sx + sy*sy;
    auto y = (sy/sx) * x + (g / (2 * s_sqr)) * x*x;

    auto new_r = std::atan((sy/sx) - (g /  s_sqr) * x) * 180 / static_cast<float>(M_PI);

    this->move(x, y);
    this->setRotation(new_r);
    ++m_tick;*/
}

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

bool Bullet::GetIsActive() const noexcept
{
    return m_isActive;
}

void Bullet::SetIsActive(bool isActive) noexcept
{
    m_isActive = isActive;
}
