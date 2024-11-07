#include <iostream>
#include <signal.h>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <fmt/core.h>
#include <fmt/chrono.h>

#include <server/server.h>
#include <server/server_pool.h>
#include <event/event_pool.h>
#include <network/http.h> 

using namespace GrowtopiaServer;
std::shared_ptr<ServerPool> g_servers;
std::shared_ptr<EventPool> g_events;

int main() {
    g_events = std::make_shared<EventPool>();
    g_events->load_events();

    HttpServer& httpServer{ HttpServer::GetHttp() };
    if (!httpServer.Listen()) {
        fmt::print("Failed to starting HttpServer, please run an external http service.\n");
        return EXIT_FAILURE;
    }
    
    g_servers = std::make_shared<ServerPool>(g_events);
    if (!g_servers->InitializeENet()) {
        fmt::print("Failed to Initialize ENet, Shutting Down the Server.\n");
        return EXIT_FAILURE;
    }

    g_servers->StartService();  
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return EXIT_SUCCESS;
}