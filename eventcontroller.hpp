// UTF-8 BOM

#ifndef EVENTCONTROLLER_HPP
#define EVENTCONTROLLER_HPP

#include "allinclusions.hpp"

using WinPtr_t   = std::shared_ptr<sf::Window>;

/**
    @brief The class management window events.
 */
class EventController : boost::noncopyable
{
public:
    using callback_t = std::function<void(sf::Event)>;

    /**
      @brief Constructor
      @param hWin
        the handle of the window whose events the object will track
     */
    EventController(WinPtr_t const &win);

    EventController(EventController &&other);

    /**
      @brief Creates a unique identifier for the event
      @param mainEv
        the main event(example: sf::Event::KeyPressed)
      @param subEv
        the 'subevent' of the main event (example sf::Event::KeyPressed, sf::Keyboard::Key::A)
      @return
        unique identifier
     */
    constexpr static inline int CreateNumber(sf::Event::EventType mainEv, int subEv = -1) noexcept;

    /**
      @brief Sets the callback to an event
      @param foo
        Callback
      @param idEvent
        Event ID received with CreateNumber
      @return
        Success of operation
      @details
        Callback is called when a transmitted event occurs
        Replaces the previous callback if it was specified
     */
    bool ConnectCallback(const callback_t &foo, int idEvent) noexcept;
    bool ConnectCallback(const callback_t &foo, sf::Event::EventType mainEv, int subEv = -1) noexcept;

    /**
      @brief StartListeningAsync
     */
    void StartListeningAsync() noexcept;

    /**
      @brief StartListeningSync
     */
    void StartListeningSync() noexcept;

    /**
      @brief Stop Listening
     */
    void StopListening() noexcept;

    ~EventController() noexcept;

private:
    WinPtr_t m_pWin;
    std::unordered_map<int, callback_t> m_mapCall;
    std::mutex m_mutex;
    bool m_isRun = false;

    /// it called when the "Closed" event arrives
    void CloseWindow__(sf::Event ev) noexcept;

    /// returns sub event if it has, else returns -1
    int GetSubEvent__(const sf::Event &ev) const noexcept;
};

template <class ...Args>
inline auto CreateWinAndController(Args && ... args)
{
    auto && win = std::make_shared<sf::Window>(args...);

    return std::pair{win, EventController(win)};
}

#endif // EVENTCONTROLLER_HPP