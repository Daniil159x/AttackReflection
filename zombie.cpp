// UTF-8 BOM

#include "allinclusions.hpp"


Zombie::Zombie() : Mob (100, 20, 100)
{
//    m_sprite.setTexture(m_frames[m_currFrame].txr);
//    m_sprite.setTextureRect(m_frames[m_currFrame].txrRect);
}

void Zombie::Eats() noexcept
{
    // TODO: что то сделать с анимацией еды
    ApplyFrame_(m_frameEat);
    m_currFrame = m_frameEat;
    // player->damage(...);
}

void Zombie::StopEats() noexcept
{
    m_currFrame = 0;
    ApplyFrame_(0);
}

void Zombie::SetFrameEats(size_t idx) noexcept
{
    m_frameEat = idx;
}

void Zombie::SetFrameDead(size_t idx) noexcept
{
    m_frameDead = idx;
}

void Zombie::Turn(float x, float y) noexcept
{
    this->move(x, y);
    if(m_currFrame != m_frameEat){
        NextFrame();
    }
}

Zombie::~Zombie() noexcept
{}

void Zombie::ApplyFrame_(size_t idx) noexcept
{
    if(m_currFrame == m_frameEat){
        return;
    }
    m_sprite.setTexture(*m_shFrames->at(idx).txr);
    m_sprite.setTextureRect(m_shFrames->at(idx).txrRect);
}

void Zombie::ApplyAlpha_(uint8_t a) noexcept
{
    auto c = m_sprite.getColor();
    c.a = a;
    m_sprite.setColor(c);
}

void Zombie::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_sprite, states);
}