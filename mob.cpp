// UTF-8 BOM

#include "allinclusions.hpp"

Animation::Animation(uint8_t callsOnFrame, uint8_t lvlDis) : Disappearing(lvlDis), m_callsOnFrame(callsOnFrame)
{}

void Animation::NextFrame() noexcept
{
    if(CheckCalls()){
        m_currFrame = (m_currFrame + 1) % m_shFrames->size();
        ApplyFrame_(m_currFrame);
    }
}

Animation::~Animation() noexcept
{}

void Animation::AppendFrameToShared(Animation::SharedFrames &tFrames, const SharedTexture &txr, const sf::IntRect &bounds) noexcept
{
    BOOST_ASSERT(tFrames);
    tFrames->emplace_back(txr, bounds);
}

void Animation::SetSharedFrames(const Animation::SharedFrames &shf) noexcept
{
    BOOST_ASSERT(shf);
    m_shFrames = shf;
    Init();
}

Animation::SharedFrames const &Animation::GetSharedFrames() const noexcept
{
    return m_shFrames;
}

void Animation::SetCallsOnFrame(const uint8_t &callsOnFrame) noexcept
{
    m_callsOnFrame = callsOnFrame;
}

void Animation::SetCurrFrame(size_t idx) noexcept
{
    m_currFrame = idx;
    ApplyFrame_(idx);
}

void Animation::Init() noexcept
{}

bool Animation::CheckCalls() noexcept
{
    ++m_countCalls;
    if(m_callsOnFrame == m_countCalls){
        m_countCalls = 0;
        return true;
    }
    return false;
}



Mob::Mob(float hp, uint8_t callsOnFrame, uint8_t lvls)
    : Animation(callsOnFrame, lvls), m_hp(hp)
{
    m_streakHP.setSize({hp, 5});
    m_streakHP.setOutlineColor(sf::Color::Black);
    m_streakHP.setOutlineThickness(2);
    m_streakHP.setFillColor(sf::Color::Green);
}

void Mob::SetHP(float hp) noexcept
{
    m_hp = hp;
}

float Mob::GetHP() const noexcept
{
    return m_hp;
}

bool Mob::Damage(float d) noexcept
{
    if(Alive() && (m_hp >= INT8_MIN + d))
    {
        m_hp -= d;
        SetHPInSteakHP_(m_hp);
        if(m_hp > 0){
            return true;
        }
        else {
            Deaded_();
            return false;
        }
    }
    return false;
}

bool Mob::Alive() const noexcept
{
    return m_hp > 0;
}

Mob::~Mob() noexcept
{}

void Mob::Deaded_() noexcept
{}

void Mob::SetHPInSteakHP_(float hp) noexcept
{
    if(hp <= 0){
        m_streakHP.setOutlineThickness(0);
        m_streakHP.setSize({});
    }
    else {
        m_streakHP.setSize({hp, 5});
    }
}

