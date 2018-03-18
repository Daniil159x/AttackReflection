// UTF-8 BOM

#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <allinclusions.hpp>

class Zombie : public Mob
{
public:
    Zombie();
    void Eats(/*Player &pl*/) noexcept;
    void StopEats(/*Player &pl*/) noexcept;
    void SetFrameEats(size_t idx) noexcept;
    void SetFrameDead(size_t idx) noexcept;
//    virtual void NextFrame() noexcept override;
    void Turn(float x, float y) noexcept;

//    virtual void NextFrame() noexcept override;

    virtual ~Zombie() noexcept override;
protected:
    virtual void ApplyFrame_(size_t idx) noexcept override;
    virtual void ApplyAlpha_(uint8_t a) noexcept override;
private:
    sf::Sprite m_sprite;
    // TODO: сделать live полосу(или прогресс бар)

    size_t m_frameEat;
    size_t m_frameDead;

//    bool

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // ZOMBIE_HPP