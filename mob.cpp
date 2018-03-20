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



Mob::Mob(int8_t hp, uint8_t callsOnFrame, uint8_t lvls)
    : Animation(callsOnFrame, lvls), m_hp(hp)
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
        if(m_hp > 0){
            return true;
        }
        else {
            Deaded();
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

void Mob::Deaded() noexcept
{}
