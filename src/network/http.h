#pragma once
#include <string>
#include <thread>
#include <httplib.h>

namespace GrowtopiaServer {
    class HttpServer {
    public:
        HttpServer() = default;
        ~HttpServer() = default;

    bool Listen();
    void Stop();

    void ServicePoll();

    public:
        static HttpServer& GetHttp() {
            static HttpServer ret;
            return ret;
        }
        
    private:
        std::unique_ptr<httplib::SSLServer> m_server;
    };
}