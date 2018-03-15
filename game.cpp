// UTF-8 BOM

#include "allinclusions.hpp"

Game::Game() : m_pWin(std::make_shared<sf::RenderWindow>(sf::VideoMode::getFullscreenModes()[0],
                                                        "Attack Reflection", sf::Style::Fullscreen)),
    m_events(m_pWin)
{
    m_pWin->setFramerateLimit(60);
    m_pWin->setKeyRepeatEnabled(false);

//    m_events.ConnectCallback([&](sf::Event ev){
//        BOOST_ASSERT(ev.type == sf::Event::Closed);
//        m_pWin->close();
//    }, sf::Event::Closed);
}

void Game::Init() noexcept
{
    m_buttons[0] = std::make_shared<Button>("Start Game");
    m_buttons[0]->GetBackground().setFillColor(sf::Color::Red);

    m_buttons[1] = std::make_shared<Button>("<Not>");
    m_buttons[1]->GetBackground().setFillColor(sf::Color::Cyan);

    m_buttons[2] = std::make_shared<Button>("Exit");
    m_buttons[2]->GetBackground().setFillColor(sf::Color::Red);

    // start
    m_events.RegisterButton(m_buttons[0], EventController::EventButtom_t::Pressed, [&]([[maybe_unused]]  EventController::EventButtom_t ev){
        m_stageGame = Launch;
    });

    // end
    m_events.RegisterButton(m_buttons[2], EventController::EventButtom_t::Pressed, [&]([[maybe_unused]] EventController::EventButtom_t ev){
        m_pWin->close();
    });

    m_events.ConnectCallback([&](sf::Event e){
        BOOST_ASSERT(e.type == sf::Event::MouseMoved);

        m_currPosCursor.x = e.mouseMove.x;
        m_currPosCursor.y = e.mouseMove.y;
    }, sf::Event::MouseMoved);


    m_skyIdx = m_textures.size();
    m_textures.push_back({});
    BOOST_ASSERT( m_textures.back().loadFromFile("../../Textures/Forest/Clouds.png") );
    m_textures.back().setRepeated(false);

    // TODO: загрузка других текстур

}

void Game::ShowMenu() noexcept
{
    uint CSize = GetCharacterSize__();

    const auto win_h = m_pWin->getSize().y;
    const auto win_w = m_pWin->getSize().x;
    sf::Vector2f winSize(m_pWin->getSize());
    for(size_t i = 0; i < m_buttons.size(); ++i)
    {
        auto &&btn = m_buttons[i];

        auto btn_w = btn->GetText().getGlobalBounds().width;
        auto btn_h = btn->GetText().getGlobalBounds().height;

        auto tCenter = sf::Vector2f(
                 win_w / 2,
                (win_h / 3) * (i + 1) - win_h / 6);

        tCenter.x -= btn_w / 2;
        tCenter.y -= btn_h / 2;

        btn->GetText().setPosition(tCenter);
        btn->GetText().setCharacterSize(CSize);
        btn->UpdateBackground();
    }

    for(auto &&sky : m_background){
        sky.setTexture(m_textures[m_skyIdx]);
        sky.setTextureRect({0, 0, static_cast<int>(win_w / 3), static_cast<int>(win_h/5)}); // TODO: продумать размеры
    }
    m_background[0].setPosition({});
    m_background[1].setPosition({100, static_cast<float>(win_h / 2)});
    m_background[0].setPosition({static_cast<float>(win_w / 2), static_cast<float>(win_h - win_h / 4)});

    std::cout << m_background[0].getTextureRect().width << " " << m_background[0].getTextureRect().height << std::endl;

    m_stageGame = Menu;
}

void Game::ShowField() noexcept
{
    m_currPosCursor = sf::Mouse::getPosition(*m_pWin);

//    m_player.setTexture(m_txrHelper.GetTexture());
//    m_player.setTextureRect(m_txrHelper.GetRectByWithOffset(1, {}));
    m_player.setPosition(0, 0); // TODO: определять позицию по карте
    m_posShots = {};

    // TODO: создание интерфейса игры
    // TODO: создание рендера
    m_events.ConnectCallback([&](sf::Event e){
        m_currPosCursor.x = e.mouseMove.x;
        m_currPosCursor.y = e.mouseMove.y;
//        std::cout << m_currPosCursor.x << " " << m_currPosCursor.y << std::endl;
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
     auto dx = UpdateMoveBackground__();

//     std::cout << dx << std::endl;

     for(auto &&sky : m_background){
         sky.move(dx, 0);
     }
}


template<>
void Game::Render__<Game::InGame>() noexcept
{
}

template<>
void Game::Render__<Game::Finish>() noexcept
{
}

template<>
void Game::Render__<Game::Launch>() noexcept
{
}

template<>
void Game::Render__<Game::Menu>() noexcept
{
    ClearWindow__();

    for(auto &&sky : m_background){
        m_pWin->draw(sky);
    }

    for(auto &&btn : m_buttons){
        m_pWin->draw(*btn);
    }
    m_pWin->display();
}

void Game::Display() noexcept
{
    if(m_stageGame == Nope){
        return;
    }

    // TODO: так как отображение меню тоже нужно рендерить, поэтому можно в Update__ менять логику действий
    std::thread([&](){
        while(m_pWin->isOpen() && m_stageGame != Nope){

            switch (m_stageGame) {
            case Finish:
                Update__<Finish>();
                Render__<Finish>();
                break;
            case InGame:
                Update__<InGame>();
                Render__<InGame>();
                break;
            case Launch:
                Update__<Launch>();
                Render__<Launch>();
                break;
            case Menu:
                Update__<Menu>();
                Render__<Menu>();
                break;
            default: ;
            }/*
            std::cout << "current: ";
            std::cout << m_currPosCursor.x << " " << m_currPosCursor.y << std::endl;

            std::cout << "old: ";
            std::cout << m_oldPosCursor.x << " " << m_oldPosCursor.y << std::endl;*/

        }
        m_events.StopListening();
    }).detach();

    m_events.StartListeningSync();
}

uint Game::GetCharacterSize__() const noexcept
{
    return 40;
}

float Game::UpdateMoveBackground__() noexcept
{
    float dx = m_oldPosCursor.x - m_currPosCursor.x;
    dx /= -30;

    m_oldPosCursor = m_currPosCursor;

    return dx;
}

void Game::ClearWindow__() noexcept
{
    m_pWin->clear(sf::Color::Cyan);
}
