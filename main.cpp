// UTF-8 BOM

#include "allinclusions.hpp"

using namespace std::chrono_literals;


int main()
{

    TextureHelper th;
    th.Load("../../test.png");
    th.MergeTexture();
    auto &&t = th.GetTexture();

    sf::Sprite red(t, th.GetRectByWithOffset(1, {8, 7, 15, 36}));
    sf::Sprite blue(t, th.GetRectByWithOffset(1, {29, 14, 18, 20}));

    red.scale(3, 3);
    blue.scale(3, 3);

    red.setPosition(90, 90);

    auto &&pWin = std::make_shared<sf::RenderWindow>(sf::VideoMode(1000, 700), "Test", sf::Style::Close);
    EventController Evc(pWin);

    pWin->setFramerateLimit(30);

    Evc.ConnectCallback([&](sf::Event e){
        auto &spr = (e.key.control) ? blue : red;

        const float mvOne = 2.f;
        float mvX = mvOne * (e.key.code == sf::Keyboard::Right) - mvOne * (e.key.code == sf::Keyboard::Left);
        float mvY = mvOne * (e.key.code == sf::Keyboard::Down) - mvOne * (e.key.code == sf::Keyboard::Up);

        spr.move(mvX, mvY);

    }, sf::Event::KeyPressed);

    std::thread([&](){
        while(pWin->isOpen()){
            pWin->clear(sf::Color::Magenta);
            pWin->draw(red);
            pWin->draw(blue);

            if(Collision::PixelPerfectTest(red, blue, th)){
                std::cout << "Collision" << std::endl;
            }

            pWin->display();
        }
    }).detach();

    Evc.StartListeningSync();


    return 0;
}
