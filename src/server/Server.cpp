//
// Created by Leo on 28/11/19.
//

#include "../client/ClientPub.hpp"
#include "Server.hpp"
#include "ServerInput.hpp"

#include <chrono>
#include <memory>

void Server::init(ServerConfig configs) {
    m_log.openLogFile(configs);
    m_log.logInfoStar("STARTING THE SERVER");

    std::map<std::string, std::string> routeConfigs = configs.getRouteConfig();
    std::vector<std::unique_ptr<ClientPub>> clientThreads;

    for (auto &element : routeConfigs) {
        std::string name = element.first;
        std::string port = element.second;
        clientThreads.push_back(std::make_unique<ClientPub>(name, port));
    }

    for (auto &element : clientThreads) {
        element->startThread();
    }

    std::string serverPort = configs.getServerPort();

    DatabaseDao db(configs);
    ServerInput client(serverPort, clientThreads, db);
    client.startThread();

    while (m_running) { std::this_thread::sleep_for(std::chrono::seconds(1)); }

    client.stopThread();
    for (auto& element: clientThreads) {
        element->stopThread();
        element->join();
    }

    client.join();
    m_log.logInfoStar("SYSTEM FINISHED SUCCESFULLY");
}

void Server::stop() {
    m_log.logInfoSlash("FINISHING THE SERVER");
    m_running = false;
}
