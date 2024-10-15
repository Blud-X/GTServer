#include <server/server.h>

namespace GrowtopiaServer {
    Server::Server(std::string& address, uint16_t port, size_t max_peers) : 
        m_address(address), m_port(port), m_max_peers(max_peers),
        m_player_pool{ std::make_shared<PlayerPool>() } {
    }
    Server::~Server() {
        if (!this->Stop())
            return;
        enet_host_destroy(this->GetHost());
    }

    bool Server::Start() {
        ENetAddress address;
        enet_address_set_host(&address, m_address.c_str());
        address.port = m_port;

        m_host = enet_host_create(&address, m_max_peers, 2, 0, 0);
        if (!m_host)
            return false;
        
        m_host->checksum = enet_crc32;
        enet_host_compress_with_range_coder(m_host);
        return true;
    }

    bool Server::Stop() {
        return true;
    }
}