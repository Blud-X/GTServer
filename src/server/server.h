#pragma once
#include <string>
#include <enet/enet.h>
#include <player/player_pool.h>

namespace GrowtopiaServer {
    class Server {
    public:
        Server(std::string& address, uint16_t port, size_t max_peers);
        ~Server();

        bool Start();
        bool Stop();

        [[nodiscard]] uint16_t GetPort() const { return m_port; }
        [[nodiscard]] std::string GetAddress() const { return m_address; }
        [[nodiscard]] ENetHost* GetHost() const { return m_host; }  

        std::shared_ptr<PlayerPool> GetPlayerPool() { return m_player_pool; }
    private:
        uint16_t m_port;
        size_t m_max_peers;
        std::string m_address{ "0.0.0.0" };

        ENetHost* m_host;

        std::shared_ptr<PlayerPool> m_player_pool;
    };
}