// UTF-8 BOM

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "allinclusions.hpp"


// TODO: реализовать иначе, так как сейчас это ужасно
//class EventController;
class Button : public sf::Drawable
{
//    friend EventController;
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

    // TODO: заменить на шарды
//    void SetEventController(EventController &ev);
//    void RemoveEventController(EventController &ev);

//    /*mutable*/ EventController &m_evC;
    sf::RectangleShape m_backfround;
    sf::Text m_text;
//    friend std::hash<Button>;
//    std::optional<size_t> m_hash;


//    void BackgroundTransform2TextTransform__() noexcept;
//    void TextTransform2BackgroundTransform__() noexcept;
};

using Button_ptr = std::shared_ptr<Button>;

//bool operator == (const Button& f, const Button& s){
//    return &f == &s; // TODO: сделать подругому
//}

//template <class T>
//bool operator == (const std::pair<Button, T> &f, const Button &btn){
//    return f.first == btn;// && f.second == s.second;
//}

//namespace std {
//    template<>
//    struct hash<Button>
//    {
//        size_t operator() (const Button& bt) const {
//            auto h1 = std::hash<const char32_t *>()(static_cast<const char32_t*>(static_cast<const void*>(bt.getString().getData())));
//            auto && p = bt.getPosition();
//            auto h2 = std::hash<uint64_t>()((static_cast<uint64_t>(p.x) << 32) || static_cast<uint32_t>(p.y));
//            return h1 ^ (h2 << 1);
//        }
//    };
//}

#endif // BUTTON_HPP_t