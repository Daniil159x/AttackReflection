// UTF-8 BOM

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "allinclusions.hpp"

class Player : public Mob
{
public:
    Player();
    void SetTextureBody(sf::Texture const& tx, sf::IntRect const &rect) noexcept;
    void SetRotateBow(float r) noexcept;
    sf::Vector2f GetCenterBow() const noexcept;
    void Shot() noexcept;
    void SetFrameShot(size_t frameShot) noexcept;
    void HoldBow() noexcept;
    void StopHoldBow() noexcept;
    int8_t GetTensionForce() const noexcept;

    virtual void NextFrame() noexcept override;
protected:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    virtual void ApplyAlpha_(uint8_t alpha) noexcept override;
    virtual void ApplyFrame_(size_t idx) noexcept override;
    virtual void Init() noexcept override;

private:
    bool m_holdBowstring = false;
//    int8_t     m_tension = 0;
    size_t     m_frameShot = 10000;
    sf::Sprite m_body;
    sf::Sprite m_bow;
    sf::Sprite m_head;

};

#endif // PLAYER_HPP