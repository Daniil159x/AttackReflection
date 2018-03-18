// UTF-8 BOM

#ifndef BULLET_HPP
#define BULLET_HPP

#include "allinclusions.hpp"

class Bullet : public Disappearing, public sf::Sprite
{
public:
    Bullet();
    Bullet(const sf::Texture& texture, const sf::IntRect& rectangle, uint8_t dmg, uint8_t lvls = 10);

    // TODO: добавить физику

    uint8_t GetDamage() const noexcept;
    void SetDamage(uint8_t damage) noexcept;

    virtual ~Bullet() noexcept override {}
protected:
    virtual void ApplyAlpha_(uint8_t alpha) noexcept;
private:
    uint8_t m_damage;
};

#endif // BULLET_HPP