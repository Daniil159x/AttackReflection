// UTF-8 BOM

#include "allinclusions.hpp"

Game::Game() : m_pWin(std::make_shared<sf::RenderWindow>(sf::VideoMode::getFullscreenModes()[0], // TODO: посмотреть другие
                                                        "Attack Reflection", sf::Style::Fullscreen)),
    m_events(m_pWin)
{
    m_pWin->setFramerateLimit(60);
    m_pWin->setKeyRepeatEnabled(false);

    m_events.ConnectCallback([&](sf::Event ev){
        BOOST_ASSERT(ev.type == sf::Event::Closed);
        m_pWin->close();
    }, sf::Event::Closed);
}

void Game::Init() noexcept
{
}

void Game::ShowMenu() noexcept
{
    uint CSize = GetCharacterSize__();

    if(!m_buttons[0]) {
        m_buttons[0] = std::make_shared<Button>("Start Game");
        m_buttons[0]->GetBackground().setFillColor(sf::Color::Red);
    }
    if(!m_buttons[1]) {
        m_buttons[1] = std::make_shared<Button>("<Not>");
        m_buttons[1]->GetBackground().setFillColor(sf::Color::Cyan);
    }
    if(!m_buttons[2]) {
        m_buttons[2] = std::make_shared<Button>("Exit");
        m_buttons[2]->GetBackground().setFillColor(sf::Color::Red);
    }

    sf::Vector2f winSize(m_pWin->getSize());
    for(size_t i = 0; i < m_buttons.size(); ++i)
    {
        auto &&btn = m_buttons[i];

        auto btn_w = btn->GetText().getGlobalBounds().width;
        auto btn_h = btn->GetText().getGlobalBounds().height;

        auto tCenter = sf::Vector2f(
                 winSize.x / 2,
                (winSize.y / 3) * (i + 1) - winSize.y / 6);

        tCenter.x -= btn_w / 2;
        tCenter.y -= btn_h / 2;

        btn->GetText().setPosition(tCenter);
        btn->GetText().setCharacterSize(CSize);
        btn->UpdateBackground();
    }
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

uint Game::GetCharacterSize__() const noexcept
{
    return 40;
}
