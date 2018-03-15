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
    // service
    WinPtr_t        m_pWin;
    EventController m_events;
//    TextureHelper   m_txrHelper;
    enum stage_t {
        /// ничего
        Nope,
        /// меню
        Menu,
        /// вход в поле игры
        Launch,
        /// в поле игры
        InGame,
        /// выход из поля игры
        Finish
    } m_stageGame = stage_t::Nope;

    // background
    std::array<sf::Sprite, 3> m_background;
    sf::Texture m_skyTexture;
    std::array<sf::Texture, 2> m_forestTexture;

    // mouse
    sf::Vector2i m_oldPosCursor;
    sf::Vector2i m_currPosCursor;
    sf::Vector2i m_posShots;

    // menu
    std::array<Button_ptr, 3> m_buttons;

    // TODO: что то сделать с текстурами
    // game loop
    Mob m_player;
    //      active
    sf::Texture m_playerTexture;
    sf::Texture m_zombieTexture;
    sf::Texture m_buttelTexture;
    //      map
    sf::Texture m_pathTexture;
    sf::Texture m_grassTexture;
    sf::Texture m_timbersTexture;
    sf::Sprite  m_path;
    sf::Sprite  m_grass;
    sf::Sprite  m_timbers;
    // TODO: опредлиться с контейнером, пока подходит только deque и лист, хотя и unordered_set
    std::deque<Mob> m_zombie;
    std::deque<Bullet> m_buttels;

    template<stage_t st>
    void Update__() noexcept;

    template<stage_t st>
    void Render__() noexcept;

    uint GetCharacterSize__() const noexcept;

    float UpdateMoveBackground__() noexcept;

    void ClearWindow__() noexcept;
};

#endif // GAME_HPP