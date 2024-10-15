#pragma once
#include <string>
#include <enet/enet.h>
#include <player/additional/packet_sender.h>

namespace GrowtopiaServer {
    class Player : public PacketSender {
    public:
        Player(ENetPeer* peer);
        ~Player() = default;

        void SetRawName(std::string& name);
        void SetDisplayName(std::string& name);

        void SetConnectID(uint32_t& connect_id);

        [[nodiscard]] std::string GetRawName() const { return m_raw_name; }
        [[nodiscard]] std::string GetDisplayName() const { return m_display_name; }

        [[nodiscard]] uint32_t GetConnectID() const {return m_connect_id; }

    private:
        ENetPeer* m_peer;

        std::string m_ip_address{};
        std::string m_raw_name{};
        std::string m_display_name{};

        uint32_t m_connect_id{ 0 };
    };
}