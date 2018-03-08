// UTF-8 BOM

#include "allinclusions.hpp"

Disappearing::Disappearing(const sf::Texture &texture, const sf::IntRect &rectangle, uint8_t lvls)
    : sf::Sprite(texture, rectangle), m_lvls(lvls)
{}

uint8_t Disappearing::GetLvls() const noexcept
{
    return m_lvls;
}

void Disappearing::SetLvls(uint8_t lvls) noexcept
{
    BOOST_ASSERT_MSG(lvls >= 1, "Number of levels must be >= 1");
    m_lvls = lvls;
}

bool Disappearing::NextLevel()
{
    auto c = getColor();
    const uint8_t step = 255 / m_lvls;
    bool hasOverflow = (c.a <= step);

    setColor({c.r, c.g, c.b, hasOverflow ? uint8_t(0) : uint8_t(c.a - step)});
    return hasOverflow;
}
