// UTF-8 BOM

#include "allinclusions.hpp"

EventController::EventController(const WinPtr_t &win) : m_pWin(win)
{
    m_mapCall.insert({CreateNumber(sf::Event::Closed),
                      [&](sf::Event ev){
                          this->CloseWindow__(ev);
                      }});
    m_pWin->setKeyRepeatEnabled(false);
}

EventController::EventController(EventController &&other)
{
    other.StopListening();
    std::lock_guard<std::mutex>(other.m_mutex);
    m_mapCall = std::move(other.m_mapCall);
    m_pWin = std::move(other.m_pWin);
}

constexpr inline int EventController::CreateNumber(sf::Event::EventType mainEv, int subEv) noexcept
{
    return ((mainEv + 1) << 16) | (subEv + 2);
}

bool EventController::ConnectCallback(const EventController::callback_t &foo, int idEvent) noexcept
{
    std::lock_guard<std::mutex> lock(m_mutex);

    m_mapCall.insert({idEvent, foo});

    return true;
}

bool EventController::ConnectCallback(const EventController::callback_t &foo, sf::Event::EventType mainEv, int subEv) noexcept
{
    return ConnectCallback(foo, CreateNumber(mainEv, subEv));
}

bool EventController::DisconnectCallback(int idEvent) noexcept
{
    std::lock_guard<std::mutex> lock(m_mutex);

    return !!m_mapCall.erase(idEvent);
}

bool EventController::DisconnectCallback(sf::Event::EventType mainEv, int subEv) noexcept
{
    return DisconnectCallback(CreateNumber(mainEv, subEv));
}

bool EventController::RegisterButton(const Button_ptr &but, EventController::EventButtom_t ev,
                                     const EventController::callbackButton_t &foo) noexcept
{
    m_arrButtons[ev].push_back({but, foo});
    return true;
}

bool EventController::UnregisterButton(const Button_ptr &but, EventController::EventButtom_t ev) noexcept
{
    auto & el = m_arrButtons[ev];
    for(auto &&it = el.begin(); it != el.end(); ++it){
        if(it->pBtn == but){
            el.erase(it);
            return true;
        }
    }
    return false;
}

void EventController::StartListeningAsync() noexcept
{
    if(!m_isRun) {
        std::thread(&EventController::StartListeningSync, this).detach();
    }
}

void EventController::StartListeningSync() noexcept
{
    if(!m_isRun) {
        m_isRun = true;

        sf::Event ev;
        uint8_t repeatErrors = 0;
        while(m_pWin->isOpen() && m_isRun){
            // TODO: приделать проверку зажатий клавиш
            if(m_pWin->waitEvent(ev) && m_isRun){
//                auto now = std::chrono::system_clock::now();
                std::unique_lock<std::mutex> lock(m_mutex);

                auto &&btnEv = SFMLEventToEventButtom__(ev);

                if(btnEv != EventButtom_t::Count){
                    bool hasCall = false;
                    // All
                    for(auto && [btn, call] : m_arrButtons[EventButtom_t::All]){
                        if(btn->getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y)){
                            lock.unlock();
                            call(EventButtom_t::All);
                            hasCall = true;
                            lock.lock();
                        }
                    }

                    // target
                    for(auto && [btn, call] : m_arrButtons[btnEv]){
                        if(btn->getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y)){
                            lock.unlock();
                            call(btnEv);
                            hasCall = true;
                            lock.lock();
                        }
                    }
                    if(hasCall){
                        continue;
                    }
                }

                int idEv = CreateNumber(ev.type, GetSubEvent__(ev));
                auto &&range = m_mapCall.equal_range(idEv);
                for(auto &&it = range.first; it != range.second; ++it){
                    lock.unlock();
                    it->second(ev);
                    lock.lock();
                }

                int idEvWithoutSub = CreateNumber(ev.type);
                if(idEvWithoutSub != idEv){
                    auto &&range = m_mapCall.equal_range(idEvWithoutSub);
                    for(auto &&it = range.first; it != range.second; ++it){
                        lock.unlock();
                        it->second(ev);
                        lock.lock();
                    }
                }

                repeatErrors = 0;

//                std::cout << std::chrono::duration_cast<std::chrono::microseconds>((std::chrono::system_clock::now() - now)).count() << "micro\n" << std::endl;
            }
            else {
                ++repeatErrors;
                if(repeatErrors >= 10){
                    sf::err() << "EventController: more than 10 errors detected - thread completion" << std::endl;
                    break;
                }
            }
        }

        m_isRun = false;
        sf::err() << "End loop EventController" << std::endl;
    }
}

void EventController::StopListening() noexcept
{
    if(m_isRun){
        m_isRun = false;
    }
}

EventController::~EventController() noexcept
{
    StopListening();
}

void EventController::CloseWindow__(sf::Event ev) noexcept
{
    BOOST_ASSERT_MSG(ev.type == sf::Event::Closed, "Type Event is not 'Closed'");

    StopListening();

    m_pWin->close();
}

int EventController::GetSubEvent__(const sf::Event &ev) const noexcept
{
    switch (ev.type) {

    case sf::Event::Event::KeyPressed:
    case sf::Event::KeyReleased:
        return ev.key.code;

    case sf::Event::MouseButtonPressed:
    case sf::Event::MouseButtonReleased:
        return ev.mouseButton.button;

    case sf::Event::MouseWheelScrolled:
        return ev.mouseWheelScroll.wheel;

    case sf::Event::SensorChanged:
        return ev.sensor.type;

    default:
        return -1;
    }
}

EventController::EventButtom_t EventController::SFMLEventToEventButtom__(const sf::Event &ev) const noexcept
{
    switch (ev.type) {
    case sf::Event::MouseButtonPressed:
        return EventButtom_t::Pressed;
    case sf::Event::MouseButtonReleased:
        return EventButtom_t::Released;
    default:
        return EventButtom_t::Count;
    }
}