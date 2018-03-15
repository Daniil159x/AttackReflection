// UTF-8 BOM

#ifndef MOB_HPP
#define MOB_HPP

#include "allinclusions.hpp"


class Mob : public Disappearing
{
public:
    Mob();
    Mob(const sf::Texture& texture, const sf::IntRect& rectangle, int8_t hp = 100, uint8_t lvls = 1);

    inline void SetHP(int8_t hp) noexcept;
    inline int8_t GetHP() const noexcept;
    inline bool Damage(int8_t d) noexcept;
    inline bool Alive() const noexcept;

private:
    int8_t m_hp;
};

#endif // MOB_HPP