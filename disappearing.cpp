// UTF-8 BOM

#include "allinclusions.hpp"

Disappearing::Disappearing()
{}

Disappearing::Disappearing(const sf::Texture &texture, const sf::IntRect &rectangle, uint8_t lvls)
    : sf::Sprite(texture, rectangle), m_lvls(lvls), m_original(getColor().a)
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

bool Disappearing::NextLevel() noexcept
{
    auto c = getColor();
    const uint8_t step = 255 / m_lvls;
    bool hasOverflow = (c.a <= step);

    setColor({c.r, c.g, c.b, hasOverflow ? uint8_t(0) : uint8_t(c.a - step)});
    return hasOverflow;
}

void Disappearing::MinLevel() noexcept
{
    auto &&c = getColor();
    setColor({c.r, c.g, c.b, 255});
}

void Disappearing::MaxLevel() noexcept
{
    auto &&c = getColor();
    setColor({c.r, c.g, c.b, 0});
}

void Disappearing::OriginalLevel() noexcept
{
    auto &&c = getColor();
    setColor({c.r, c.g, c.b, m_original});
}
