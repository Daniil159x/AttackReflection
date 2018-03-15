// UTF-8 BOM

#include "allinclusions.hpp"

using namespace std::chrono_literals;


int main()
{
    Button::GlobalFontInit();
/*
    auto &&pWin = std::make_shared<sf::RenderWindow>(sf::VideoMode(900, 400), "Test", sf::Style::Close);
    EventController Evc(pWin);

    pWin->setFramerateLimit(30);

//    auto pBtn = std::make_shared<Button>("Text");
//    pBtn->GetBackground().setFillColor(sf::Color::Red);
//    pBtn->GetText().setPosition(50, 50);
//    pBtn->GetText().setCharacterSize(50);
//    pBtn->UpdateBackground({20, 20});


    TextureHelper helper;
    auto idx = helper.Load("../../5.png", 5);
    auto idx2 = helper.Load("../../4.png", 5);

    helper.MergeTexture();

    sf::Sprite s(helper.GetTexture(), helper.GetRectBy(idx));
    sf::Vector2f pos(60, 60);
    s.setPosition(pos);

    sf::Sprite s2(helper.GetTexture(), helper.GetRectBy(idx2));
    sf::Vector2f pos2(40, 40);
    s.setPosition(pos2);

//    std::cout << sf::Mouse::getPosition(*pWin).x << std::endl;
    sf::Vector2f oldPosMouse, currPosMouse = {};
    int offSet = 0;
    Evc.ConnectCallback([&](sf::Event e){
        currPosMouse.x = e.mouseMove.x;
        currPosMouse.y = e.mouseMove.y;
    }, sf::Event::MouseMoved);

    Evc.ConnectCallback([&](sf::Event e){
        std::cout << "Mouse pressed" << std::endl;
    }, sf::Event::MouseButtonPressed);

    std::thread([&](){
        while(pWin->isOpen()){
            pWin->clear(sf::Color::Magenta);

            auto dx = oldPosMouse.x - currPosMouse.x;

            dx /= -30;

            std::cout << dx << std::endl;
            const float MaxOff = 5;
//            if(dx > MaxOff){
//                dx = MaxOff;
//            }
//            else if(dx < -MaxOff){
//                dx = -MaxOff;
//            }

            oldPosMouse = currPosMouse;

//            s2.setPosition(pos2.x - offSet / 2, pos2.y);
            s2.move(dx/3, 0);
            pWin->draw(s2);

            s.move(dx, 0);
//            s.setPosition(pos.x - offSet, pos.y);
            pWin->draw(s);
            pWin->display();



        }
    }).detach();

    Evc.StartListeningSync();*/


    Game gm;
    gm.Init();
    gm.ShowMenu();
    gm.Display();

    return 0;
}
