// UTF-8 BOM

#ifndef GAME_HPP
#define GAME_HPP

#include "allinclusions.hpp"

// TODO
class Mob {};
class Bullet {};

// главный класс игры, создаёт внутри себя контроллер и рендер(view), управлет моделями и логикой игры
class Game
{
public:
    Game();

    // инициализация игры, создаение окна, рендера и контролера, начальные бинды
    void Init();
    // выводит представление меню
    void ShowMenu();
    // переход к другому виду - игры
    void ShowField();
    // начало игры
    void Start();
    // конец игры, заверщающее меню(представление)
    void ShowEndGame();
    // внешнее прерывание игры
//    void Stop();
private:
    Mob m_player;
    // TODO: опредлиться с контейнером, пока подходит только deque и лист, хотя и unordered_set
    std::deque<Mob> m_zombie;
    std::deque<Bullet> m_buttels;


};

#endif // GAME_HPP