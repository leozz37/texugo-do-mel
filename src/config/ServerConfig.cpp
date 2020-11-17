//
// Created by Leo on 18/12/19.
//

#include "ServerConfig.hpp"

#include <nlohmann/json.hpp>

nlohmann::json ServerConfig::getServerConfigs() {
    std::ifstream i(m_serverConfigPath);
    std::string jsonData = std::string(std::istreambuf_iterator<char>(i), std::istreambuf_iterator<char>());
    nlohmann::json serverConfig = nlohmann::json::parse(jsonData);
    return serverConfig;
}

void ServerConfig::setRouteConfig(nlohmann::json m_data) {
    for (auto &i : m_data["routeConfig"]) {
        std::map<std::string, std::string> data = i.get<std::map<std::string, std::string>>();
        m_routeConfig.insert(data.begin(), data.end());
    }
}

