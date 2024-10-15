#pragma once
#include <functional>
#include <player/player.h>
#include <server/server.h>
#include <proton/packet.h>
#include <proton/utils/text_scanner.h>

namespace GrowtopiaServer {
    class EventPool;
    class ServerPool;
    enum eEventType {
        EVENT_TYPE_GENERIC_TEXT,
        EVENT_TYPE_ACTION,
        EVENT_TYPE_GAME_PACKET,
        NUM_EVENTS
    };
    struct EventContext {
        std::shared_ptr<Player> m_player;
        std::shared_ptr<EventPool> m_events;
        std::shared_ptr<Server> m_server;
        ServerPool* m_servers;

        TextScanner m_parser;
        GameUpdatePacket* m_update_packet;
    };
}