// UTF-8 BOM

#include "allinclusions.hpp"

#define ROOT_PATH "../../"

Game::Game() : m_pWin(std::make_shared<sf::RenderWindow>(sf::VideoMode::getFullscreenModes()[0],
                                                        "Attack Reflection"/*, sf::Style::Fullscreen*/)),
    m_events(m_pWin), m_zombieFrames(std::make_shared<std::vector<Animation::Frame_t>>())
{
//    m_pWin->setFramerateLimit(60);
    m_pWin->setVerticalSyncEnabled(true);
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
        ShowField();
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

//    m_events.ConnectCallback([&](sf::Event e){
//        BOOST_ASSERT(e.type == sf::Event::TouchMoved);

//        m_currPosCursor.x = e.touch.x;
//        m_currPosCursor.y = e.touch.y;
//    }, sf::Event::TouchMoved);


    // background
    BOOST_ASSERT( m_skyTexture.loadFromFile(ROOT_PATH "Textures/Forest/Clouds.png") );
    BOOST_ASSERT( m_forestTexture[0].loadFromFile(ROOT_PATH "Textures/Forest/Forest back.png") );
    BOOST_ASSERT( m_forestTexture[1].loadFromFile(ROOT_PATH "Textures/Forest/Forest front.png") );
    m_skyTexture.setRepeated(true);
    m_forestTexture[0].setRepeated(true);
    m_forestTexture[1].setRepeated(true);

    // game
    BOOST_ASSERT( m_playerTexture.loadFromFile(ROOT_PATH "Textures/Archer/Archer.png") );

    SharedTexture tmp;
    for(uint i = 1; i <= 6; ++i) {
        tmp = std::make_shared<sf::Texture>();
        tmp->loadFromFile(ROOT_PATH "Textures/Zombie/Zombie " + std::to_string(i) + ".png");
        const auto [w, h] = sf::Vector2i(tmp->getSize());
        Animation::AppendFrameToShared(m_zombieFrames, tmp, {0, 0, w, h});
    }

//    BOOST_ASSERT( m_zombieTexture.loadFromFile(ROOT_PATH "Textures/Zombie/Zombie 1.png") );
    BOOST_ASSERT( m_buttelTexture.loadFromFile(ROOT_PATH "Textures/Archer/Arrow.png") );

    // map
    BOOST_ASSERT( m_pathTexture.loadFromFile(ROOT_PATH "Textures/Forest/Path.png") );
    BOOST_ASSERT( m_grassTexture.loadFromFile(ROOT_PATH "Textures/Forest/Grass.png") );
    m_pathTexture.setRepeated(true);
    m_grassTexture.setRepeated(true);
    BOOST_ASSERT( m_timbersTexture.loadFromFile(ROOT_PATH "Textures/Forest/Timbers.png") );

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

        auto tCenter = sf::Vector2f( win_w / 2,
                (win_h / 3) * (i + 1) - win_h / 6);

        tCenter.x -= btn_w / 2;
        tCenter.y -= btn_h / 2;

        btn->GetText().setPosition(tCenter);
        btn->GetText().setCharacterSize(CSize);
        btn->UpdateBackground();
    }

    for(auto &&sky : m_background){
        sky.setTexture(m_skyTexture);
        sky.setTextureRect({0, 0, static_cast<int>(win_w / 4), static_cast<int>(win_h/6)}); // TODO: продумать размеры
    }
    m_background[0].setPosition({});
    m_background[1].setPosition({100, static_cast<float>(win_h / 2)});
    m_background[2].setPosition({static_cast<float>(win_w / 2), static_cast<float>(win_h - win_h / 4)});

    m_stageGame = Menu;
}

void Game::ShowField() noexcept
{
    const int win_w = static_cast<int>(m_pWin->getSize().x) + 100;

    // TODO: сделать кастомную ориентацию текстур
    m_background[0].setTextureRect({0, 0, win_w, m_background[0].getTextureRect().height});
    m_background[0].setPosition(20, 100);

    m_background[1].setTexture(m_forestTexture[0], true);
    m_background[1].setTextureRect({0, 0, win_w + 200, m_background[1].getTextureRect().height});
    m_background[1].setPosition(-150, 600);

    m_background[2].setTexture(m_forestTexture[1], true);
    m_background[2].setTextureRect({0, 0, win_w + 200, m_background[2].getTextureRect().height});
    m_background[2].setPosition(-150, 650);

    m_path.setTexture(m_pathTexture, true);
    m_path.setTextureRect({0, 0, win_w, m_path.getTextureRect().height });
    m_path.setPosition(-10, 980);

    m_timbers.setTexture(m_timbersTexture, true);
    m_timbers.setPosition(9, 800);

//    m_player.setTexture(m_playerTexture, true);
//    m_player.setPosition(85, 630);

    m_zombie.push_back({});
    m_zombie.back().SetSharedFrames(m_zombieFrames);
    m_zombie.back().SetSharedFrames(m_zombieFrames);
    m_zombie.back().SetFrameEats(m_zombieFrames->size() - 1);
    m_zombie.back().setPosition(1986, 770);

    m_grass.setTexture(m_grassTexture, true);
    m_grass.setTextureRect({0, 0, win_w, m_grass.getTextureRect().height });
    m_grass.setPosition(-8, 1030);

//    m_events.ConnectCallback([&](sf::Event e){
//    }, sf::Event::MouseButtonPressed);

//    m_stageGame = Launch;

    m_buttons.back()->GetText().setPosition(1800, 30);
    m_buttons.back()->UpdateBackground({10, 10});


    m_events.ConnectCallback([&](sf::Event e){
        m_zombie.back().Eats();
    }, sf::Event::KeyPressed, sf::Keyboard::Q);

    m_events.ConnectCallback([&](sf::Event e){
        m_zombie.back().StopEats();
    }, sf::Event::KeyReleased, sf::Keyboard::W);


    m_stageGame = InGame;
}


template<>
void Game::Update__<Game::InGame>() noexcept
{
    auto dx = UpdateMoveBackground__();

    for(auto &&z : m_zombie){
        z.Turn(-1.f, 0);
    }

    m_background[0].move(dx/6, 0);
    m_background[1].move(dx/3, 0);
    m_background[2].move(dx/1, 0);
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
    ClearWindow__();

    // небо, лес
    for(auto &&back : m_background){
        m_pWin->draw(back);
    }
    // тропа
    m_pWin->draw(m_path);

    // платформа
    m_pWin->draw(m_timbers);

    // игрок
//    m_pWin->draw(m_player);

    // зомби
    for(auto && z : m_zombie){
        m_pWin->draw(z);
    }

    // стрелы
    for(auto && b : m_buttels){
        m_pWin->draw(b);
    }

    // трава
    m_pWin->draw(m_grass);

    m_pWin->draw(*m_buttons.back());

    m_pWin->display();
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
            }
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
