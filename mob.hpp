// UTF-8 BOM

#ifndef MOB_HPP
#define MOB_HPP

#include "allinclusions.hpp"
using SharedTexture = std::shared_ptr<sf::Texture>;

class Animation : public Disappearing, public sf::Drawable, public sf::Transformable
{
public:

    struct Frame_t {
        Frame_t(const SharedTexture & t, sf::IntRect const &rect) : txr(t), txrRect(rect) {}
        SharedTexture txr;
        sf::IntRect   txrRect;
    };
    using SharedFrames = std::shared_ptr<std::vector<Frame_t>>;

    Animation(uint8_t callsOnFrame = 1, uint8_t lvlDis = 10);
    virtual void NextFrame() noexcept;
    virtual ~Animation() noexcept override;

    static void AppendFrameToShared(SharedFrames &tFrames, const SharedTexture &txr, const sf::IntRect &bounds) noexcept;

    void SetSharedFrames(SharedFrames const &shf) noexcept;
    const SharedFrames &GetSharedFrames() const noexcept;
    void SetCallsOnFrame(const uint8_t &callsOnFrame) noexcept;
    void SetCurrFrame(size_t idx) noexcept;

protected:

    SharedFrames         m_shFrames;
    size_t               m_currFrame = 0;
    uint8_t              m_callsOnFrame;
    uint8_t              m_countCalls = 0;

    virtual void ApplyFrame_(size_t idx) noexcept = 0;
    virtual void Init() noexcept;

    bool CheckCalls() noexcept;
};


class Mob : public Animation
{
public:
    Mob(int8_t hp = 100, uint8_t callsOnFrame = 1, uint8_t lvls = 10);

    void SetHP(int8_t hp) noexcept;
    int8_t GetHP() const noexcept;
    bool Damage(int8_t d) noexcept;
    bool Alive() const noexcept;

    virtual ~Mob() noexcept override;
protected:
    int8_t m_hp;

    virtual void Deaded() noexcept;
};

#endif // MOB_HPP