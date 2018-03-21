// UTF-8 BOM

#include "allinclusions.hpp"


Zombie::Zombie() : Mob (100, 20, 100)
{
    m_streakHP.setFillColor(sf::Color::Red);
}

void Zombie::Eats(Player &pl) noexcept
{
    // TODO: что то сделать с анимацией еды
    ApplyFrame_(m_frameEat);
    m_currFrame = m_frameEat;
    pl.Damage(0.5f);
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
    m_streakHP.setPosition(this->getPosition() + sf::Vector2f{20, -20});
    if(m_currFrame != m_frameEat){
        NextFrame();
    }
}

bool Zombie::IsCollision(sf::Vector2f p) const noexcept
{
    if(!getTransform().transformRect(m_sprite.getLocalBounds()).contains(p)){
        return false;
    }
    // TODO: КОСТЫЛЬ
    static std::unordered_map<sf::Texture const*, sf::Image> mp;

    const auto key = m_sprite.getTexture();
    if(mp.find(key) == mp.end()){
        mp.emplace(key, key->copyToImage());
    }
    p -= this->getPosition();

    auto a = mp[key].getPixel(static_cast<uint>(p.x), static_cast<uint>(p.y)).a;

    return a > 200;
}

sf::FloatRect Zombie::GetGlobalBounds() const noexcept
{
    return this->getTransform().transformRect(m_sprite.getLocalBounds());
}

Zombie::~Zombie() noexcept
{}

void Zombie::ApplyFrame_(size_t idx) noexcept
{
    if(m_currFrame == m_frameEat || m_currFrame == m_frameDead){
        m_currFrame = 0;
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
    target.draw(m_streakHP);
}

void Zombie::Deaded_() noexcept
{
    m_currFrame = m_frameDead;
}