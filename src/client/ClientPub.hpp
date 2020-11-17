//
// Created by Leo on 03/12/19.
//

#ifndef CORE_CLIENTPUB_HPP
#define CORE_CLIENTPUB_HPP

#include "../config/ServerConfig.hpp"
#include "../config/LogConfig.hpp"
#include "MessageServer.hpp"

#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

class ClientPub : public MessageServer {
public:
    ClientPub(std::string _id, std::string _route);
    void inputQueue(std::string t_message);
    virtual void openPort() override;
    const std::string &getId() const;
private:
    std::string m_id;
    std::queue<std::string> m_queue;
};

#endif //CORE_CLIENTPUB_HPP
