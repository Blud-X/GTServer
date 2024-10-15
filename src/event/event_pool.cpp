#include <event/event_pool.h>
#include <fmt/core.h>
#include <algorithm>

#include <event/text_events/action.h>

namespace GrowtopiaServer {
    EventPool::EventPool() {
        fmt::print("Intiliazing EventPool\n");
    }
    EventPool::~EventPool() {
        this->unload_events();
    }

    void EventPool::load_events() {
        register_generic("action", events::action);

        fmt::print(" - registered events, {} genetric texts {} actions {} game packets\n",
        this->get_registered_event(EVENT_TYPE_GENERIC_TEXT),
        this->get_registered_event(EVENT_TYPE_ACTION),
        this->get_registered_event(EVENT_TYPE_GAME_PACKET));
    }
    void EventPool::unload_events() {
        m_events.clear();
    }

    void EventPool::register_generic(const std::string& ev, std::function<void(EventContext&)> fn) {
        m_events[EVENT_TYPE_GENERIC_TEXT].push_back({ utils::quick_hash(ev), fn });
    }
    void EventPool::register_action(const std::string& ev, std::function<void(EventContext&)> fn) {
        m_events[EVENT_TYPE_ACTION].push_back({ utils::quick_hash(ev), fn });
    }
    void EventPool::register_packet(const uint8_t& ev, std::function<void(EventContext&)> fn) {
        m_events[EVENT_TYPE_GAME_PACKET].push_back({ utils::quick_hash("gup_" + std::to_string(ev)), fn });
    }

    std::size_t EventPool::get_registered_event(const eEventType& type) const {
        if (auto it = m_events.find(type); it == m_events.end())
            return std::size_t{ 0 };
        return m_events.at(type).size();
    }
}