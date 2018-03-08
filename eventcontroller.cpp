// UTF-8 BOM

#include "allinclusions.hpp"

EventController::EventController(const WinPtr_t &win) : m_pWin(win)
{
    m_mapCall[ CreateNumber(sf::Event::Closed) ] = [&](sf::Event ev){
        this->CloseWindow__(ev);
    };
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

    m_mapCall.insert_or_assign(idEvent, foo);

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
            // TODO: приложение остановится не сразу, так как должно наступить какое то событие
            // TODO: приделать проверку зажатий клавиш
            if(m_pWin->waitEvent(ev) && m_isRun){
                std::unique_lock<std::mutex> lock(m_mutex);

                int idEv = CreateNumber(ev.type, GetSubEvent__(ev));

//                std::cout << "Event = " << idEv << std::endl;

                auto &&it = m_mapCall.find(idEv);

                if(it == m_mapCall.end()){

                    idEv = CreateNumber(ev.type);
                    it = m_mapCall.find(idEv);

                    if(it != m_mapCall.end()){
                        lock.unlock(); // TODO: скорее костыль, надо через рекурсивный mutex
                        it->second.operator()(ev);
                    }
                }
                else if(m_isRun){
                    lock.unlock(); // TODO: скорее костыль, надо через рекурсивный mutex
                    it->second.operator()(ev);
                }
                repeatErrors = 0;
            }
            else {
                ++repeatErrors;
                if(repeatErrors >= 10){
                    sf::err() << "EventController loop ended with errors" << std::endl;
                    break;
                }
                // TODO: error log
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