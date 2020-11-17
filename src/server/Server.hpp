//
// Created by Leo on 28/11/19.
//

#ifndef CORE_SERVER_HPP
#define CORE_SERVER_HPP

#include "../config/ServerConfig.hpp"
#include "../config/LogConfig.hpp"

#include <thread>

class Server {
public:
    void init(ServerConfig configs);
    void stop();

private:
    bool m_running = true;
    LogConfig m_log;
};

#endif //CORE_SERVER_HPP
