//
// Created by Leo on 03/12/19.
//

#ifndef CORE_SERVERINPUT_HPP
#define CORE_SERVERINPUT_HPP

#include "../client/ClientPub.hpp"
#include "../config/ServerConfig.hpp"
#include "../client/MessageServer.hpp"
#include "../config/PayloadConfig.hpp"
#include "../database/DatabaseDao.hpp"

#include <thread>
#include <zmq.hpp>

class ServerInput : public MessageServer {
public:
    ServerInput(std::string m_port, std::vector<std::unique_ptr<ClientPub>>& m_clients, DatabaseDao& m_db);
    virtual void openPort() override;
private:
    std::vector<std::unique_ptr<ClientPub>>& m_clients;
    DatabaseDao& m_db;
    short handleDestination(std::string t_recipient);
    void inputQueue(const PayloadConfig& payload);
};

#endif //CORE_SERVERINPUT_HPP
