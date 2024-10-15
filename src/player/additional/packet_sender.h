#pragma once
#include <fmt/format.h>
#include <enet/enet.h>
#include <proton/packet.h>
#include <proton/variant.h>
#include <proton/utils/text_scanner.h>

namespace GrowtopiaServer {
    class PacketSender {
    public:
        PacketSender(ENetPeer* peer) : m_peer(peer) {}
        ~PacketSender() = default;
        [[nodiscard]] ENetPeer* GetPeer() { return m_peer; }

        void SendPacket(TankUpdatePacket tank_packet, uintmax_t data_size) {
            if (!this->GetPeer())
                return;
            ENetPacket* packet = enet_packet_create(nullptr, data_size, ENET_PACKET_FLAG_RELIABLE);
            if (!packet)
                return;
            std::memcpy(packet->data, &tank_packet, data_size);
            if (enet_peer_send(m_peer, 0, packet) != 0)
                enet_packet_destroy(packet);
        }
        void SendPacket(TankUpdatePacket* tank_packet, uintmax_t data_size) {
            if (!this->GetPeer())
                return;
            GameUpdatePacket* update_packet = reinterpret_cast<GameUpdatePacket*>(&tank_packet->m_data); 
            ENetPacket* packet = enet_packet_create(nullptr, data_size, ENET_PACKET_FLAG_RELIABLE);
            if (!packet || !update_packet)
                return;
            std::memcpy(packet->data, &tank_packet->m_type, 4);
            std::memcpy(packet->data + 4, update_packet, sizeof(GameUpdatePacket) + update_packet->m_data_size);

            if (enet_peer_send(m_peer, 0, packet) != 0)
                enet_packet_destroy(packet);
        }
        void SendPacket(eNetMessageType type, const void* data, uintmax_t data_size) {
            if (!this->GetPeer())
                return;
            ENetPacket* packet = enet_packet_create(nullptr, 5 + data_size, ENET_PACKET_FLAG_RELIABLE);
            if (!packet)
                return;
            std::memcpy(packet->data, &type, 4);
            packet->data[data_size + 4] = 0;
            
            if (data)
                std::memcpy(packet->data + 4, data, data_size);

            if (enet_peer_send(m_peer, 0, packet) != 0)
                enet_packet_destroy(packet);
        }
        
        template <typename... Args>
        void SendLog(const std::string& format, Args&&... args) {
            const auto& data = fmt::format("action|log\nmsg|{}", fmt::vformat(format, fmt::make_format_args(args...)));
            this->SendPacket(NET_MESSAGE_GAME_MESSAGE, data.data(), data.size());
        }
        void PlaySfx(const std::string& sound, const int32_t& delay) {
            TextScanner parser{};
            parser.add("action", "play_sfx");
            parser.add("file", fmt::format("audio/{}.wav", sound));
            parser.add<int32_t>("delayMS", delay);
            const auto& data{ parser.get_all_raw() };
            this->SendPacket(NET_MESSAGE_GAME_MESSAGE, data.data(), data.size());
        }
        void SendDanceAnimation(int32_t net_id) {
            TextScanner parser{};
            parser.add("action", "animation");
            parser.add("type", "8");
            parser.add<int32_t>("netID", net_id);
            const auto& data{ parser.get_all_raw() };
            this->SendPacket(NET_MESSAGE_GAME_MESSAGE, data.data(), data.size());
        }
        void SendSetURL(const std::string& url, const std::string& label) {
            TextScanner parser{};
            parser.add("action", "set_url");
            parser.add("url", url);
            parser.add("label", label);
            const auto& data{ parser.get_all_raw() };
            this->SendPacket(NET_MESSAGE_GAME_MESSAGE, data.data(), data.size());
        }
        void SendVariant(const variantlist_t& var, int32_t delay = 0, int32_t net_id = -1) {
            size_t alloc = 1;
            for(const auto& v : var.get_objects()) 
                alloc += v.get_memory_allocate() + 1;
            const uint8_t* var_data = var.serialize();
            
            GameUpdatePacket* update_packet = reinterpret_cast<GameUpdatePacket*>(std::malloc(sizeof(GameUpdatePacket) + alloc));
            update_packet->m_type = NET_GAME_PACKET_CALL_FUNCTION;
            update_packet->m_net_id = net_id;
            update_packet->m_flags |= NET_GAME_PACKET_FLAGS_EXTENDED;
            update_packet->m_delay = delay;
            update_packet->m_data_size = static_cast<uint32_t>(alloc);
            std::memcpy(&update_packet->m_data, var_data, alloc);

            this->SendPacket(NET_MESSAGE_GAME_PACKET, update_packet, sizeof(GameUpdatePacket) + update_packet->m_data_size);    
            std::free(update_packet);
        }

    private:
        ENetPeer* m_peer;
    };
}