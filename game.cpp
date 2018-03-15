// UTF-8 BOM

#include "allinclusions.hpp"

Game::Game() : m_pWin(std::make_shared<sf::RenderWindow>(sf::VideoMode::getFullscreenModes()[0], // TODO: посмотреть другие
                                                        "Attack Reflection"/*, sf::Style::Fullscreen*/)),
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
    m_events.RegisterButton(m_buttons[0], EventController::EventButtom_t::Pressed, [&](EventController::EventButtom_t ev){
        m_stageGame = Launch;
    });

    // end
    m_events.RegisterButton(m_buttons[2], EventController::EventButtom_t::Pressed, [&](EventController::EventButtom_t ev){
        m_pWin->close();
    });

    m_events.ConnectCallback([&](sf::Event e){
        BOOST_ASSERT(e.type == sf::Event::MouseMoved);

        m_currPosCursor.x = e.mouseMove.x;
        m_currPosCursor.y = e.mouseMove.y;
    }, sf::Event::MouseMoved);


    // загрузка текстур
    m_skyIdx = m_txrHelper.Load("", 2);
//    m_forestIdx1 = m_txrHelper.Load("", 5); // TODO: размеры!
//    m_forestIdx2 = m_txrHelper.Load("", 5);

    m_txrHelper.MergeTexture();
    m_events.StartListeningSync();
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

    for(size_t i = 0; i < m_background.size(); ++i){
        m_background[i].setTexture(m_txrHelper.GetTexture());
        m_background[i].setTextureRect(m_txrHelper.GetRectBy(m_skyIdx));

        m_background[i].setPosition((win_w / 3) * i, (win_h / 3) * i );
    }
    m_stageGame = Menu;
}

void Game::ShowField() noexcept
{
    m_currPosCursor = sf::Mouse::getPosition(*m_pWin);

    m_player.setTexture(m_txrHelper.GetTexture());
    m_player.setTextureRect(m_txrHelper.GetRectByWithOffset(1, {}));
    m_player.setPosition(0, 0); // TODO: определять позицию по карте
    m_posShots = {};

    // TODO: создание интерфейса игры
    // TODO: создание рендера
    m_events.ConnectCallback([&](sf::Event e){
        m_currPosCursor.x += e.mouseMove.x;
        m_currPosCursor.y += e.mouseMove.y;
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
    if(m_stageGame != Nope){
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
            }
            m_oldPosCursor = m_currPosCursor;
        }
        m_events.StopListening();
    }).detach();
}

uint Game::GetCharacterSize__() const noexcept
{
    return 40;
}

float Game::UpdateMoveBackground__() noexcept
{
    float dx = m_oldPosCursor.x - m_currPosCursor.x;
    dx /= -30;

    return dx;
}
