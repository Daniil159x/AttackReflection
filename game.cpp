// UTF-8 BOM

#include "allinclusions.hpp"

Game::Game() : m_pWin(std::make_shared<sf::RenderWindow>(sf::VideoMode::getFullscreenModes()[0], // TODO: посмотреть другие
                                                        "Attack Reflection", sf::Style::Fullscreen)),
    m_events(m_pWin)
{
    m_pWin->setFramerateLimit(60);
    m_pWin->setKeyRepeatEnabled(false);
}

void Game::Init() noexcept
{
    // TODO: загрузка текстур
    // TODO: регистация кнопок
}

void Game::ShowField() noexcept
{
    m_posCursor = sf::Mouse::getPosition(*m_pWin);

    m_player.setTexture(m_txrHelper.GetTexture());
    m_player.setTextureRect(m_txrHelper.GetRectByWithOffset(1, {}));
    m_player.setPosition(0, 0); // TODO: определять позицию по карте
    m_posShots = {};

    // TODO: создание интерфейса игры
    // TODO: создание рендера
    m_events.ConnectCallback([&](sf::Event e){
        m_posCursor.x += e.mouseMove.x;
        m_posCursor.y += e.mouseMove.y;
        // TODO: вращать лук(или игрока)
        // TODO: анимация фона
    }, sf::Event::MouseMoved);

    m_events.ConnectCallback([&](sf::Event e){
        // TODO: расчитать вектор
        // TODO: может быть сделать анимацию титевы
    }, sf::Event::MouseButtonPressed);

    m_stageGame = Launch;
}


template<>
void Game::Update__<Game::InGame>() noexcept
{
    for(auto &&b : m_buttels){
        // TODO: шаг снарядов
    }

    for(auto &&z : m_zombie) {
        // TODO: шаг зомби
    }
}

template<>
void Game::Update__<Game::Finish>() noexcept
{
    // TODO: анимация конца
}

template<>
void Game::Update__<Game::Launch>() noexcept
{
    // TODO: анимация начала
}

template<>
void Game::Update__<Game::Menu>() noexcept
{
    // nope
}

void Game::Display() noexcept
{
    if(m_stageGame != Nope){
        return;
    }

    // TODO: так как отображение меню тоже нужно рендерить, поэтому можно в Update__ менять логику действий
    std::thread([&](){
        while(m_pWin->isOpen() && m_stageGame != Nope){

            switch (m_stageGame) {
            case Finish:
                Update__<Finish>();
                break;
            case InGame:
                Update__<InGame>();
                break;
            case Launch:
                Update__<Launch>();
                break;
            case Menu:
                Update__<Menu>();
                break;
            default: ;

            }

            Render__();
        }
        m_events.StopListening();
    }).detach();


    m_events.StartListeningSync(); // TODO: убрать так как изначально слушать начнёт в ShowMenu
}

void Game::Render__() noexcept
{
    // TODO: добавить рендер
}
