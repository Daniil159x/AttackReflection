// UTF-8 BOM

#include "allinclusions.hpp"

Disappearing::Disappearing(uint8_t lvls)
    : m_lvls(lvls), m_currAlpha(m_original)
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
    const uint8_t step = 255 / m_lvls;
    bool hasOverflow = (m_currAlpha <= step);

    m_currAlpha -= step;

    ApplyAlpha_(m_currAlpha);
    return hasOverflow;
}

void Disappearing::MinLevel() noexcept
{
    ApplyAlpha_(255);
}

void Disappearing::MaxLevel() noexcept
{
    ApplyAlpha_(0);
}

void Disappearing::OriginalLevel() noexcept
{
    ApplyAlpha_(m_original);
}
