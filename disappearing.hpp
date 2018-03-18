// UTF-8 BOM

#ifndef DISAPPEARING_HPP
#define DISAPPEARING_HPP

#include "allinclusions.hpp"

class Disappearing
{
public:
    Disappearing(uint8_t lvls = 1);

    inline uint8_t GetLvls() const noexcept;
    inline void SetLvls(uint8_t lvls = 1) noexcept;

    virtual bool NextLevel() noexcept;
    void MinLevel() noexcept;
    void MaxLevel() noexcept;
    void OriginalLevel() noexcept;

    virtual ~Disappearing() noexcept {}
protected:
    virtual void ApplyAlpha_(uint8_t alpha) noexcept = 0;
    void SetOriginal_(uint8_t oringin) noexcept;
private:
    uint8_t m_lvls = 1;
    uint8_t m_original = 255;
    uint8_t m_currAlpha;
};

#endif // DISAPPEARING_HPP