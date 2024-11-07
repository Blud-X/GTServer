#include <config.h>
#include <fmt/core.h>
#include <network/http.h>
#include <proton/utils/text_scanner.h>

namespace GrowtopiaServer {
    bool HttpServer::Listen() {
        fmt::print("Starting HttpServer, binding port to server\n");

        m_server = std::make_unique<httplib::SSLServer>("./cache/cert.pem", "./cache/key.pem");

        if (!m_server->bind_to_port("0.0.0.0", 443)) {
            fmt::print("Failed to bind port 443 to HttpServer.\n");
            return false;
        }

        std::thread(&HttpServer::ServicePoll, this).detach();
        fmt::print("HttpServer Initialized, Listening to https://0.0.0.0:443\n");
        return true;
    }
    void HttpServer::Stop() { 
        m_server->stop();
        m_server.release();
    }

    void HttpServer::ServicePoll() {
        m_server->Post("/growtopia/server_data.php", [&](const httplib::Request& req, httplib::Response& res) {
            TextScanner parser{};
            parser.add("server", std::string{ config::gt_login::m_ip_address });
            parser.add<uint16_t>("port", config::gt_login::m_port);
            parser.add("loginurl", "blud-loginurl.vercel.app");
            parser.add<int>("type", 1);
            parser.add("#maint", "Server is under maintenance. We will be back online shortly. Thank you for your patience!");
            parser.add("meta", "GTSERVER");
            res.set_content(std::string{ fmt::format("{}\nRTENDMARKERBS1001\n\n", parser.get_all_raw()) }, "text/html");
        });
        
        m_server->listen_after_bind();
        while(true);
    }
}