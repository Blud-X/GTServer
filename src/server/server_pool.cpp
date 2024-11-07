#include <fmt/core.h>
#include <server/server_pool.h>
#include <event/event_context.h>
#include <event/event_pool.h>
#include <fmt/chrono.h>
#include <enet/enet.h>
#include <magic_enum.hpp>
#include <player/player.h>

namespace GrowtopiaServer {
    ServerPool::ServerPool(std::shared_ptr<EventPool> events) : 
        PacketDecoder{ },
        m_events{ events } {
        fmt::print("Initializing ServerPool\n");
    }
    ServerPool::~ServerPool() {
        enet_deinitialize();
    }

    bool ServerPool::InitializeENet() {
        if (enet_initialize() != 0) {
            fmt::print("Failed to Initialize ENet server\n");
            return false;
        }
        return true;
    }
    void ServerPool::DeInitializeENet() {
        enet_deinitialize();
    }

    bool ServerPool::StartServer() {
        m_server = std::make_shared<Server>(m_address, m_port, m_max_peers);
        if (!m_server->Start()) {
            fmt::print("Failed to Start ENet Server -> {}:{}", m_server->GetAddress(), m_server->GetPort());
            return false;
        }
        fmt::print("Starting Server -> {}:{} - {}\n", m_server->GetAddress(), m_server->GetPort(), std::chrono::system_clock::now());
        return true;
    }

    void ServerPool::StartService() {
        if (m_running.load())
            return;
        if (!StartServer())
            return;

        m_running.store(true);
        m_threads.push_back(std::thread{ &ServerPool::ServicePoll, this });
        for (auto& thread : m_threads)
            thread.detach();
    }
    void ServerPool::StopService() {
        if (!m_running.load())
            return;
        m_running.store(false);
    }
    void ServerPool::ServicePoll() {
        try {
        ENetEvent event{};
        while (m_running.load()) {
            while (enet_host_check_events(m_server->GetHost(), &event)) {
                if (!event.peer)
                    break;

                switch(event.type) {
                    case ENET_EVENT_TYPE_CONNECT: {
                        std::shared_ptr<Player> player{ m_server->GetPlayerPool()->NewPlayer(event.peer) };
                        player->SendPacket({ NET_MESSAGE_SERVER_HELLO }, sizeof(TankUpdatePacket));
                        break;
                    }
                    case ENET_EVENT_TYPE_DISCONNECT: {
                        if (!event.peer->data)
                            break;
                        std::uint32_t connect_id{};
                        std::memcpy(&connect_id, event.peer->data, sizeof(std::uint32_t));
                        std::free(event.peer->data);
                        event.peer->data = NULL;

                        std::shared_ptr<Player> player{ m_server->GetPlayerPool()->GetPlayer(connect_id) };
                        if (!player)
                            return;

                        m_server->GetPlayerPool()->RemovePlayer(connect_id);
                        break;
                    }
                    case ENET_EVENT_TYPE_RECEIVE: {
                        if (event.packet->dataLength < sizeof(TankUpdatePacket::m_type) + 1 || event.packet->dataLength > 0x400) {
                            enet_packet_destroy(event.packet);
                            break;
                        }
                        std::shared_ptr<Player> player = std::make_shared<Player>(event.peer);

                        switch (*((int32_t*)event.packet->data)) {
                        case NET_MESSAGE_GENERIC_TEXT:
                        case NET_MESSAGE_GAME_MESSAGE: {
                            const auto& str = PacketDecoder::DataToString(event.packet->data + 4, event.packet->dataLength - 4);
                            EventContext ctx{
                                .m_player = player,
                                .m_events = this->GetEvents(),
                                .m_server = m_server,
                                .m_servers = this,
                                .m_parser = TextScanner{ str },
                                .m_update_packet = nullptr
                            };
                            std::string event_data = str.substr(0, str.find('|'));
                            if (!m_events->execute(EVENT_TYPE_GENERIC_TEXT, event_data, ctx))
                                break;
                        }
                        case NET_MESSAGE_GAME_PACKET: {
                            GameUpdatePacket* update_packet = this->DataToUpdatePacket(event.packet);
                            if (!update_packet)
                                break;

                            EventContext ctx{
                                .m_player = player,
                                .m_events = this->GetEvents(),
                                .m_server = m_server,
                                .m_servers = this,
                                .m_parser = TextScanner{},
                                .m_update_packet = update_packet
                            };

                            if (!m_events->execute(EVENT_TYPE_GAME_PACKET, "gup_" + std::to_string(update_packet->m_type), ctx)) {
                                fmt::print("unhandled EVENT_TYPE_GAME_PACKET -> `w{}`o", magic_enum::enum_name(static_cast<eNetPacketType>(update_packet->m_type)));
                                break;
                            }
                        }
                        }
                        enet_packet_destroy(event.packet);
                        break;
                    }
                    case ENET_EVENT_TYPE_NONE:
                    default:
                        break;
                    }
                }
                enet_host_service(m_server->GetHost(), nullptr, 0);
            }
        } catch (std::exception& e) {
            fmt::print("ServerPool >> {}\n", e.what());
        }
    }
}
