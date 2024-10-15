#pragma once
#include <memory>
#include <unordered_map>
#include <enet/enet.h>
#include <player/player.h>

namespace GrowtopiaServer {
    class PlayerPool {
    public:
        PlayerPool() = default;
        ~PlayerPool() = default;

        std::shared_ptr<Player> NewPlayer(ENetPeer* peer) {
            m_players[peer->connectID] = std::make_shared<Player>(peer);
            return m_players[peer->connectID];
        }
        void RemovePlayer(uint32_t connect_id) {
            m_players[connect_id].reset();
            m_players.erase(connect_id);
        }
        std::shared_ptr<Player> GetPlayer(const uint32_t& cid) {
            for (auto& [connect_id, player] : m_players) {
                if (connect_id == cid)
                    return player;
            }
            return nullptr;
        }
    public:
        [[nodiscard]] std::unordered_map<uint32_t, std::shared_ptr<Player>> const GetPlayers() { return m_players; }
        [[nodiscard]] std::size_t GetPlayerCount() const { return m_players.size(); }

    private:
        std::unordered_map<uint32_t, std::shared_ptr<Player>> m_players{};
    };
}