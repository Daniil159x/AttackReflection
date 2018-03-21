// UTF-8 BOM

#ifndef BULLET_HPP
#define BULLET_HPP

#include "allinclusions.hpp"

class Bullet : public Disappearing, public sf::Sprite
{
public:
    Bullet(const sf::Texture& texture, const sf::IntRect& rectangle, float dmg, uint8_t lvls = 10);

    void Tick(float dx) noexcept;

    float GetDamage() const noexcept;
    void SetDamage(float damage) noexcept;

    virtual ~Bullet() noexcept override {}
    bool GetActive() const noexcept;
    void SetActive(bool isActive) noexcept;

protected:
    virtual void ApplyAlpha_(uint8_t alpha) noexcept override;
private:
    float m_damage;
    bool  m_isActive;
//    uint    m_tick; // = time
};

#endif // BULLET_HPP