#include <player/player.h>

namespace GrowtopiaServer {
    Player::Player(ENetPeer* peer) : 
        m_peer(peer),
        PacketSender{ peer },
        v_sender{ peer } {
        if(!m_peer)
            return;
        m_peer->data = std::malloc(sizeof(uint32_t));
        std::memcpy(m_peer->data, &m_peer->connectID, sizeof(uint32_t));

        m_ip_address.reserve(16);
        enet_address_get_host_ip(&m_peer->address, m_ip_address.data(), 16);
        this->SetConnectID(m_peer->connectID);
    }

    void Player::SetRawName(std::string& name) {
        this->m_raw_name = name;
    }
    void Player::SetDisplayName(std::string& name) {
        this->m_display_name = name;
    }

    void Player::SetConnectID(uint32_t& connect_id) {
        this->m_connect_id = connect_id;
    }
}