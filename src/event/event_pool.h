#pragma once
#include <string>
#include <functional>
#include <unordered_map>
#include <vector>
#include <event/event_context.h>
#include <fmt/core.h>

namespace GrowtopiaServer {
    class EventPool {
    public:
        using event_list = std::vector<std::pair<uint32_t, std::function<void(EventContext&)>>>;
        using event_type = std::unordered_map<eEventType, event_list>;

    public:
        EventPool();
        ~EventPool();

        void load_events();
        void unload_events();

        void register_generic(const std::string& ev, std::function<void(EventContext&)> fn);
        void register_action(const std::string& ev, std::function<void(EventContext&)> fn);
        void register_packet(const uint8_t& ev, std::function<void(EventContext&)> fn);

        std::size_t get_registered_event(const eEventType& type) const;

        bool execute(const eEventType& type, const std::string& data, EventContext& ctx) {
            const auto& it = m_events.find(type);
            if (it == m_events.end())
                return false;

            const uint32_t& ev_hash{ utils::quick_hash(data) };
            for (const auto& ev : it->second) {
                if (ev_hash != ev.first)
                    continue;
                ev.second(ctx);
                return true;
            }
            return false;
        }

    private:
        event_type m_events;
    };
}
