// UTF-8 BOM

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "allinclusions.hpp"


class Button : public sf::Drawable
{
public:
    Button(const sf::String& string, const sf::Font& font = GlobalFont, unsigned int characterSize = 30);

    sf::RectangleShape & GetBackground() noexcept;
    sf::Text & GetText() noexcept;

    inline static sf::Font GlobalFont;
    static void GlobalFontInit();

    void UpdateBackground(sf::Vector2f padding = {20, 20}) noexcept;
    void UpdateText(sf::Vector2f padding = {20, 20}) noexcept;
    sf::FloatRect getGlobalBounds() const noexcept;

    void SetPressed(bool pressed) noexcept;

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::RectangleShape m_backfround;
    sf::Text m_text;
};

using Button_ptr = std::shared_ptr<Button>;

#endif // BUTTON_HPP_t