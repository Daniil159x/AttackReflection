// UTF-8 BOM

#ifndef GAME_HPP
#define GAME_HPP

#include "allinclusions.hpp"

//using Mob = sf::Sprite;
//using Bullet = sf::Sprite;

/// главный класс игры, создаёт внутри себя контроллер и рендер(view), управлет моделями и логикой игры
class Game : boost::noncopyable
{
public:
    Game();

    /// инициализация игры, создаение окна, рендера и контролера, начальные бинды
    void Init() noexcept;
    /// выводит представление меню
    void ShowMenu() noexcept;
    /// переход к другому виду - игры
    void ShowField() noexcept;
    /// начало игры
    void Display() noexcept;
    /// конец игры, заверщающее меню(представление)
    void ShowEndGame() noexcept;
    /// внешнее прерывание игры
//    void Stop();
    void Pause() noexcept;
private:
    WinPtr_t        m_pWin;
    EventController m_events;
    TextureHelper   m_txrHelper;
    enum stage_t {
        Nope,
        Menu,
        Launch,
        InGame,
        Finish
    } m_stageGame = stage_t::Nope;

    Mob m_player;
    sf::Vector2i m_posCursor;
    sf::Vector2u m_posShots;
    // TODO: опредлиться с контейнером, пока подходит только deque и лист, хотя и unordered_set
    std::deque<Mob> m_zombie;
    std::deque<Bullet> m_buttels;

    template<stage_t st>
    void Update__() noexcept;

    void Render__() noexcept;
};

#endif // GAME_HPP