// UTF-8 BOM

#ifndef BULLET_HPP
#define BULLET_HPP

#include "allinclusions.hpp"

class Bullet : public Disappearing, public sf::Sprite
{
public:
    Bullet(const sf::Texture& texture, const sf::IntRect& rectangle, uint8_t dmg, uint8_t lvls = 10);

    void Tick(float dx) noexcept;

    uint8_t GetDamage() const noexcept;
    void SetDamage(uint8_t damage) noexcept;

    virtual ~Bullet() noexcept override {}
    bool GetIsActive() const noexcept;
    void SetIsActive(bool isActive) noexcept;

protected:
    virtual void ApplyAlpha_(uint8_t alpha) noexcept override;
private:
    uint8_t m_damage;
    bool    m_isActive;
//    uint    m_tick; // = time
};

#endif // BULLET_HPP