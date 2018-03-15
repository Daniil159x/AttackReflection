// UTF-8 BOM


#ifndef TEXTUREHELPER_HPP
#define TEXTUREHELPER_HPP

#include "allinclusions.hpp"

// класс абстрогирующий загрузку текстур и доступ к пикселям текстур
// TODO: добавить компановку
class TextureHelper
{
public:
    TextureHelper();
    // загрузить текстуру в память, возвращает id изображения
    size_t Load(boost::filesystem::path const &file, uint8_t repeat = 1) noexcept;
    // создаёт единую текстуру
    void MergeTexture() noexcept;
    // выдать текстуру, если текстура не создана, то создаётся
    const sf::Texture &GetTexture() const noexcept;
    const sf::Texture &GetTexture() noexcept;
    // выдать rect в текстуре соответвующее этому изображению
    const sf::IntRect &GetRectBy(size_t id) const;
    // тоже самое только со смещением
    sf::IntRect GetRectByWithOffset(size_t id, sf::IntRect rect) const;
    // получить цвет пикселя
    sf::Color GetPixel(uint x, uint y) const;
private:
    std::vector<sf::Image>   m_tmp;
    sf::Vector2u             m_tmpSize;

    std::vector<sf::IntRect> m_frames;
    sf::Image                m_mainImages;
    sf::Texture              m_texture;
};

#endif // TEXTUREHELPER_HPP