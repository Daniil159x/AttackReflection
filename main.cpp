// UTF-8 BOM

#include "allinclusions.hpp"

using namespace std::chrono_literals;

int main()
{
    auto && [pWin, EvC] = CreateWinAndController(sf::VideoMode(600, 400), "Test", sf::Style::Close);

    pWin->setFramerateLimit(60);

    EvC.ConnectCallback([](sf::Event ev){

        std::cout << "Pressed Key: " << ev.key.code << std::endl;

    }, sf::Event::KeyPressed);

    EvC.StartListeningAsync();

    while(pWin->isOpen()){
        pWin->display();
    }

    return 0;
}
