// UTF-8 BOM

#include "allinclusions.hpp"

using namespace std::chrono_literals;

Game::Game() : m_pWin(std::make_shared<sf::RenderWindow>(sf::VideoMode::getFullscreenModes()[0],
                                                        "Attack Reflection"/*, sf::Style::Fullscreen*/)),
    m_events(m_pWin), m_archerBowFrames(std::make_shared<std::vector<Animation::Frame_t>>()),
    m_zombieFrames(std::make_shared<std::vector<Animation::Frame_t>>()), m_delayFinish(std::chrono::duration_cast<duration_t>(5s))
{
    m_pWin->setFramerateLimit(60);
//    m_pWin->setVerticalSyncEnabled(true);
    m_pWin->setKeyRepeatEnabled(false);

    m_endText.setFont(Button::GlobalFont);
    m_endText.setString("GAME OVER");
    m_endText.setCharacterSize(100);
    m_endText.setFillColor(sf::Color::Red);
    m_endText.setStyle(sf::Text::Regular);

    auto [x, y, w, h]   = m_endText.getLocalBounds();
    auto [x_win, y_win] = m_pWin->getSize();

    m_endText.setPosition( x_win/2 - w/2, y_win/2 - h/2);

    m_lastTimeZombie = clock_t::now();
    UpdateRandDelayZombie__();
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


    // background
    BOOST_ASSERT( m_skyTexture.loadFromFile(ROOT_PATH "Textures/Forest/Clouds.png") );
    BOOST_ASSERT( m_forestTexture[0].loadFromFile(ROOT_PATH "Textures/Forest/Forest back.png") );
    BOOST_ASSERT( m_forestTexture[1].loadFromFile(ROOT_PATH "Textures/Forest/Forest front.png") );
    m_skyTexture.setRepeated(true);
    m_forestTexture[0].setRepeated(true);
    m_forestTexture[1].setRepeated(true);

    // game
    SharedTexture tmp;

    BOOST_ASSERT( m_archerBody.loadFromFile(ROOT_PATH "Textures/Archer/Aiming and shooting/Archer without hands.png") );
    const auto [w, h] = sf::Vector2i(m_archerBody.getSize());
    m_player.SetTextureBody(m_archerBody, {0, 0, w, h});
    //  player
    for(uint i = 1; i <= 5; ++i){
        tmp = std::make_shared<sf::Texture>();
        tmp->loadFromFile(ROOT_PATH "Textures/Archer/Aiming and shooting/Hands " + std::to_string(i) + ".png");
        const auto [w, h] = sf::Vector2i(tmp->getSize());
        Animation::AppendFrameToShared(m_archerBowFrames, tmp, {0, 0, w, h});
    }
    m_player.SetSharedFrames(m_archerBowFrames);
    m_player.SetCallsOnFrame(30);

    //  zombie
    for(uint i = 1; i <= 6; ++i) {
        tmp = std::make_shared<sf::Texture>();
        tmp->loadFromFile(ROOT_PATH "Textures/Zombie/Zombie " + std::to_string(i) + ".png");
        const auto [w, h] = sf::Vector2i(tmp->getSize());
        Animation::AppendFrameToShared(m_zombieFrames, tmp, {0, 0, w, h});
    }

    BOOST_ASSERT( m_bulletTexture.loadFromFile(ROOT_PATH "Textures/Archer/Arrow.png") );

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


    m_player.SetTextureBody(m_archerBody, {0, 0, static_cast<int>(m_archerBody.getSize().x),
                                                 static_cast<int>(m_archerBody.getSize().y)});
    m_player.SetSharedFrames(m_archerBowFrames);
    m_player.SetFrameShot(3);
    m_player.setPosition(30, 630);
    m_player.SetRotateBow(0);

    m_grass.setTexture(m_grassTexture, true);
    m_grass.setTextureRect({0, 0, win_w, m_grass.getTextureRect().height });
    m_grass.setPosition(-8, 1030);

    m_events.ConnectCallback([&](sf::Event e){
        if(e.mouseButton.button == sf::Mouse::Left){
            m_pressedLBtn = true;
        }
    }, sf::Event::MouseButtonPressed);

    m_events.ConnectCallback([&](sf::Event e){
        if(e.mouseButton.button == sf::Mouse::Left){
            m_pressedLBtn = false;
        }
    }, sf::Event::MouseButtonReleased);

    m_stageGame = Launch;

    m_buttons.back()->GetText().setPosition(1800, 30);
    m_buttons.back()->UpdateBackground({10, 10});
}


template<>
void Game::Update__<Game::InGame>() noexcept
{

    auto dx = UpdateMoveBackground__();
    m_background[0].move(dx/6, 0);
    m_background[1].move(dx/3, 0);
    m_background[2].move(dx/1, 0);

    // игрок    
    auto r = CalculateRotate(m_player.GetCenterBow(), sf::Vector2f(m_currPosCursor));
    m_player.SetRotateBow(r);

    auto forse = m_player.GetTensionForce();
    if(forse > 1 && !m_pressedLBtn){
        const auto [x, y] = m_bulletTexture.getSize();
        auto &&b = m_bullets.emplace_back(m_bulletTexture, sf::IntRect{0, 0, static_cast<int>(x), static_cast<int>(y)}, 50);
        b.setPosition(m_player.GetCenterBow());
        b.setRotation(m_player.GetRotateBow());
        b.SetLvls(50);
        b.SetActive(true);
        b.SetDamage(forse);
        m_player.Shot();
    }

    const auto now = clock_t::now();
    if((now - m_lastTimeZombie) >= m_delayZombie){
//        std::cout << "create: " << m_delayZombie.count() << "ns" << std::endl;
        CreateZombie__();
        UpdateRandDelayZombie__();
        m_lastTimeZombie = now;
    }

    // стрелы
    const auto WinRect = sf::FloatRect{0, 0, static_cast<float>(m_pWin->getSize().x),
                                             static_cast<float>(m_pWin->getSize().y) };
    for(auto &&it = m_bullets.begin(); it != m_bullets.end();){        
        const auto [w, h] = m_bulletTexture.getSize();
        const auto tip    = it->getTransform().transformPoint(w, h/2);
        const auto line_y   = m_path.getPosition().y + m_pathTexture.getSize().y / 2;

        if( tip.y >= line_y ){
            it->SetActive(false);
        }
        if(!it->GetActive()){
            if(it->NextLevel()){
                it = m_bullets.erase(it);
            }
            else{
                ++it;
            }
            continue;
        }

        it->Tick(10);

        // коллизии
        for(auto &&z : m_zombie){
            if(z.Alive() && z.IsCollision(tip)){
                it->SetActive(false);
                z.Damage(it->GetDamage());
                break;
            }
        }

        if(!WinRect.contains(it->getPosition())){
            it = m_bullets.erase(it);
        }
        else {
            ++it;
        }
    }


    // зомби
    for(auto &&it = m_zombie.begin(); it != m_zombie.end();){
        if(it->Alive()){

            const auto [x, y, w, h] = it->GetGlobalBounds();
            const auto x_target = x + w/2;

            const auto x_player = m_player.getPosition().x + 270;
            if(x_player >= x_target){
                it->Eats(m_player);
                ++it;
                continue;
            }
            const auto x_stairs_end = m_timbers.getPosition().x + 525;
            const auto x_stairs_begin = m_timbers.getPosition().x + 280;
            const float dx = -1;
            if(x_stairs_begin <= x_target && x_target <= x_stairs_end){
                it->Turn(dx, dx * 145.f / 206.f);
            }
            else {
                it->Turn(dx, 0);
            }
        }
        else {
            if(it->NextLevel()){
                it = m_zombie.erase(it);
            }
            else {
                ++it;
            }
            continue;
        }
        ++it;
    }


    if(!m_player.Alive()){
        m_startFinish = clock_t::now();
        m_stageGame   = Finish;
    }
}

template<>
void Game::Update__<Game::Finish>() noexcept
{
    auto now = clock_t::now();
    if((now - m_startFinish) >= m_delayFinish){
        ShowMenu();
    }
}

template<>
void Game::Update__<Game::Launch>() noexcept
{
    // TODO: анимация начала
    m_stageGame = InGame;
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
    // небо, лес
    for(auto &&back : m_background){
        m_pWin->draw(back);
    }
    // тропа
    m_pWin->draw(m_path);

    // платформа
    m_pWin->draw(m_timbers);

    // игрок
    if(m_player.GetTensionForce() != 0 || m_pressedLBtn){
        m_player.NextFrame();
    }
    m_pWin->draw(m_player);

    // зомби
    for(auto && z : m_zombie){
        m_pWin->draw(z);
    }

    // стрелы
    for(auto && b : m_bullets){
        m_pWin->draw(b);
    }

    // трава
    m_pWin->draw(m_grass);

    m_pWin->draw(*m_buttons.back());
}

template<>
void Game::Render__<Game::Finish>() noexcept
{
    Render__<InGame>();
    m_pWin->draw(m_endText);
    auto [x, y, w, h] = m_endText.getGlobalBounds();
//    std::cout << x << " " << y << " " << w << " " << h << std::endl;
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

    std::thread([&](){
        while(m_pWin->isOpen() && m_stageGame != Nope){

            ClearWindow__();

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

            m_pWin->display();
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

void Game::CreateZombie__() noexcept
{
    m_zombie.push_back({});
    auto &&z = m_zombie.back();
    z.SetSharedFrames(m_zombieFrames);
    z.SetFrameEats(m_zombieFrames->size() - 1);
    z.setPosition(1986, 840);
    z.SetCallsOnFrame(15);
}

void Game::UpdateRandDelayZombie__() noexcept
{
    static std::mt19937 gen(static_cast<std::mt19937::result_type>(clock_t::now().time_since_epoch().count()));

    static std::uniform_int_distribution<> dis(2, 10);

    m_delayZombie = std::chrono::seconds(dis(gen));
}
