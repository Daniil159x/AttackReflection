// UTF-8 BOM


#include "allinclusions.hpp"
/*
// TODO: улучшить обнаружение
bool Collision::PixelPerfectTest(const sf::Sprite &obj_1, const sf::Sprite &obj_2, sf::Uint8 AlphaLimit)
{
    BOOST_ASSERT_MSG(obj_1.getTexture() == &helper.GetTexture() &&
                     obj_2.getTexture() == &helper.GetTexture(), "Texture must be coincide");

    sf::FloatRect inter;
    if(obj_1.getGlobalBounds().intersects(obj_2.getGlobalBounds(), inter)){
        auto &&tRect_1 = obj_1.getTextureRect();
        auto &&tRect_2 = obj_2.getTextureRect();
        const sf::IntRect inter_int(inter);

        const int x_w = inter_int.left + inter_int.width;
        const int y_h = inter_int.top + inter_int.height;

        const auto &matrixObj_1 = obj_1.getInverseTransform();
        const auto &matrixObj_2 = obj_2.getInverseTransform();

        for(int x = inter_int.left; x < x_w; ++x){
            for(int y = inter_int.top; y < y_h; ++y){

                const auto &vecObj_1 = matrixObj_1.transformPoint(x, y);
                const auto &vecObj_2 = matrixObj_2.transformPoint(x, y);


                if(vecObj_1.x > 0 && vecObj_1.y > 0 &&
                   vecObj_2.x > 0 && vecObj_2.y > 0 &&
                   vecObj_1.x < tRect_1.width && vecObj_1.y < tRect_1.height &&
                   vecObj_2.x < tRect_2.width && vecObj_2.y < tRect_2.height)
                {
                    if(helper.GetPixel(static_cast<uint>(vecObj_1.x + tRect_1.left), static_cast<uint>(vecObj_1.y + tRect_1.top)).a > AlphaLimit &&
                       helper.GetPixel(static_cast<uint>(vecObj_2.x + tRect_2.left), static_cast<uint>(vecObj_2.y + tRect_2.top)).a > AlphaLimit)
                    {
                        return true;
                    }
                }

            }
        }

    }
    return false;
}*/
