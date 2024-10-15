#pragma once
#include <string>
#include <memory>
#include <thread>
#include <vector>
#include <atomic>
#include <server/server.h>
#include <proton/packet.h>

namespace GrowtopiaServer {
    class EventPool;
    class ServerPool : PacketDecoder {
    public:
        ServerPool(std::shared_ptr<EventPool> events);
        ~ServerPool();

        bool InitializeENet();
        void DeInitializeENet();

        bool StartServer();

        void StartService();
        void StopService();
        void ServicePoll();

    public:
        std::shared_ptr<EventPool> GetEvents() const { return m_events; }
    
    private:
        std::string m_address{ "0.0.0.0" };
        uint16_t m_port{ 17091 };
        size_t m_max_peers{ 0xFF };

        std::atomic<bool> m_running{ false };
        std::vector<std::thread> m_threads{};

    private:
        std::shared_ptr<EventPool> m_events;
        std::shared_ptr<Server> m_server;

    };
}