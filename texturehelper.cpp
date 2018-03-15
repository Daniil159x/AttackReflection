// UTF-8 BOM

#include "allinclusions.hpp"


TextureHelper::TextureHelper() : m_tmpSize(0, 0)
{}

size_t TextureHelper::Load(const boost::filesystem::path &file, uint8_t repeat) noexcept
{
    sf::Image img_loaded;
    if(!img_loaded.loadFromFile(file.generic_string())){
        return 0;
    }

    m_tmp.push_back({});
    auto &img_res = m_tmp.back();

    auto w = img_loaded.getSize().x;
    auto h = img_loaded.getSize().y;

    img_res.create(w * repeat, h, sf::Color::Transparent);
    for(uint8_t i = 0; i < repeat; ++i){
        img_res.copy(img_loaded, w * i, 0);
    }


    m_tmpSize.x += img_res.getSize().x;
    m_tmpSize.y = std::max(m_tmpSize.y, img_res.getSize().y);

    return m_tmp.size() + m_frames.size();
}

void TextureHelper::MergeTexture() noexcept
{
    if(m_tmp.size() == 0){
        return;
    }

    sf::Image tmp_target;
    if(m_mainImages.getSize() != sf::Vector2u{0, 0}){
        m_tmpSize.x += m_mainImages.getSize().x;
        m_tmpSize.y = std::max(m_mainImages.getSize().y, m_tmpSize.y);
    }
    tmp_target.create(m_tmpSize.x, m_tmpSize.y, sf::Color::Transparent);
    tmp_target.copy(m_mainImages, 0, 0);
    auto destX = m_mainImages.getSize().x;
    for(auto &&currImg : m_tmp){
        tmp_target.copy(currImg, destX, 0);
        m_frames.push_back({static_cast<int>(destX), 0,
                            static_cast<int>(currImg.getSize().x), static_cast<int>(currImg.getSize().y)});
        destX += currImg.getSize().x;
    }
    m_tmp.clear();
    m_tmpSize.x = 0;
    m_tmpSize.y = 0;
    m_mainImages = tmp_target; // TODO: убрать копирование
    m_texture.loadFromImage(m_mainImages);
}

const sf::Texture &TextureHelper::GetTexture() const noexcept
{
    return m_texture;
}

const sf::Texture &TextureHelper::GetTexture() noexcept
{
    if(m_texture.getSize() == sf::Vector2u(0, 0)){
        MergeTexture();
    }
    return m_texture;
}


const sf::IntRect &TextureHelper::GetRectBy(size_t id) const
{
    return m_frames.at(id - 1);
}

sf::IntRect TextureHelper::GetRectByWithOffset(size_t id, sf::IntRect rect) const
{
    auto &&r = m_frames.at(id - 1);
    rect.left += r.left;
    rect.top  += r.top;

    return rect;
}

sf::Color TextureHelper::GetPixel(uint x, uint y) const
{
    if(!(x < m_mainImages.getSize().x && y < m_mainImages.getSize().y)){
        throw std::out_of_range(BOOST_CURRENT_FUNCTION + std::string(": ") + std::to_string(x) + ", " + std::to_string(y));
    }
    return m_mainImages.getPixel(x, y);
}
