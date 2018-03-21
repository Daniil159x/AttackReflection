// UTF-8 BOM

#include "allinclusions.hpp"

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= this->getTransform();
    target.draw(m_body, states);
    target.draw(m_bow);
    target.draw(m_head);
}

void Player::ApplyAlpha_(uint8_t alpha) noexcept
{
    auto c = m_body.getColor();
    c.a = alpha;
    m_body.setColor(c);

    c = m_bow.getColor();
    c.a = alpha;
    m_bow.setColor(c);
}

void Player::ApplyFrame_(size_t idx) noexcept
{
    m_bow.setTexture(*m_shFrames->at(idx).txr);
    m_bow.setTextureRect(m_shFrames->at(idx).txrRect);
}

void Player::Init() noexcept
{
    m_bow.setOrigin(110, 165);
    ApplyFrame_(0);
}

Player::Player()
{}

void Player::SetTextureBody(const sf::Texture &tx, const sf::IntRect &rect) noexcept
{
    m_body.setTexture(tx);
    m_body.setTextureRect(rect);

    m_head.setTexture(tx);
    m_head.setTextureRect({120, 0, 35, 39});
}

void Player::SetRotateBow(float r) noexcept
{
    if(-45 <= r && r <= 30){
        m_bow.setPosition(this->getPosition() + sf::Vector2f{127, 45});
        m_bow.setRotation(r - 18.2084f);

        m_head.setPosition(this->getPosition() + sf::Vector2f{120, 0});
    }
}

float Player::GetRotateBow() const noexcept
{
    return m_bow.getRotation() + 18.2084f;
}

sf::Vector2f Player::GetCenterBow() const noexcept
{
    return this->getPosition() + sf::Vector2f{127, 45};
}

void Player::Shot() noexcept
{
    //BOOST_ASSERT(m_holdBowstring);
    StopHoldBow();
    m_currFrame = m_shFrames->size() - m_currFrame;
    if(m_currFrame >= m_shFrames->size()){
        m_currFrame = 0;
    }
    ApplyFrame_(m_currFrame);
}

void Player::SetFrameShot(size_t frameShot) noexcept
{
    m_frameShot = frameShot;
}

int8_t Player::GetTensionForce() const noexcept
{
    BOOST_ASSERT(m_shFrames->size() <= 127);
    const int8_t forse_one = std::numeric_limits<int8_t>::max() / m_shFrames->size();
    if(m_currFrame < m_frameShot){
        return static_cast<int8_t>(m_currFrame) * forse_one;
    }
    else {
        auto r_idx = m_shFrames->size() - m_frameShot;
        return static_cast<int8_t>(r_idx) * -forse_one;
    }
}

void Player::NextFrame() noexcept
{
    if(CheckCalls()){
        if(GetTensionForce() >= 0){
            m_currFrame = (m_currFrame + 1) < m_frameShot ? m_currFrame + 1 : m_currFrame;
        }
        else if(GetTensionForce() < 0){
            m_currFrame = (m_currFrame + 1) % m_shFrames->size();
        }
        else {
            return;
        }
        ApplyFrame_(m_currFrame);
    }
}

bool Player::HoldBow() noexcept
{
    m_holdBowstring = true;
    return m_holdBowstring;
}

void Player::StopHoldBow() noexcept
{
    m_holdBowstring = false;
}
