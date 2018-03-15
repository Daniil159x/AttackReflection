// UTF-8 BOM

#include "allinclusions.hpp"

using namespace std::chrono_literals;


int main()
{
    Button::GlobalFontInit();

    auto &&pWin = std::make_shared<sf::RenderWindow>(sf::VideoMode(1000, 700), "Test", sf::Style::Close);
    EventController Evc(pWin);

    pWin->setFramerateLimit(30);

    auto pBtn = std::make_shared<Button>("Text");
    pBtn->GetBackground().setFillColor(sf::Color::Red);
    pBtn->GetText().setPosition(50, 50);
    pBtn->GetText().setCharacterSize(50);
    pBtn->UpdateBackground({20, 20});

    Evc.RegisterButton(pBtn, EventController::Released, [&](auto ev){
        std::cout << "Released" << std::endl;
    });

    Evc.RegisterButton(pBtn, EventController::Pressed, [&](auto ev){
        std::cout << "Press" << std::endl;
    });

//    Evc.ConnectCallback([&](sf::Event ev){
//        auto r = CalculateRotate(pBtn->GetText().getOrigin(),
//        { static_cast<float>(ev.mouseMove.x), static_cast<float>(ev.mouseMove.y) });

//        std::cout << "calc = " << r << std::endl;
//        pBtn->GetText().setRotation( r );
//        pBtn->UpdateBackground();
//    }, sf::Event::MouseMoved);

    Evc.ConnectCallback([&](sf::Event ev){
        std::cout << sf::Mouse::getPosition(*pWin).x << " " << sf::Mouse::getPosition(*pWin).y << std::endl;
        std::cout << "pos " << pBtn->GetText().getPosition().x << " " << pBtn->GetText().getPosition().y << std::endl;
    }, sf::Event::MouseButtonReleased, sf::Mouse::Left);


    std::thread([&](){
        while(pWin->isOpen()){
            pWin->clear(sf::Color::Magenta);

            pWin->draw(*pBtn);

            pWin->display();
        }
    }).detach();

    Evc.StartListeningSync();


    return 0;
}
