// UTF-8 BOM

#include "allinclusions.hpp"

Button::Button(const sf::String &string, const sf::Font& font, unsigned int characterSize)
    : m_text(string, font, characterSize)
{
    UpdateBackground();
}

sf::RectangleShape & Button::GetBackground() noexcept
{
    return m_backfround;
}

sf::Text &Button::GetText() noexcept
{
    return m_text;
}

void Button::GlobalFontInit()
{
    GlobalFont.loadFromFile(ROOT_PATH "Fonts/11602.ttf");
}

void Button::UpdateBackground(sf::Vector2f padding) noexcept
{
    // TODO: сделать поворот

    float x = m_text.getGlobalBounds().left - padding.x;
    float y = m_text.getGlobalBounds().top  - padding.y;
    m_backfround.setPosition(x, y);

    float w = m_text.getLocalBounds().width  + padding.x * 2;
    float h = m_text.getLocalBounds().height + padding.y * 2;
    m_backfround.setSize({w, h});

    m_backfround.setScale(m_text.getScale());
}

void Button::UpdateText(sf::Vector2f padding) noexcept
{
}

sf::FloatRect Button::getGlobalBounds() const noexcept
{
    return m_backfround.getGlobalBounds();
}

void Button::draw(sf::RenderTarget &target, [[maybe_unused]] sf::RenderStates states) const
{
    target.draw(m_backfround);
    target.draw(m_text);
}