//
// Created by Leo on 19/11/19.
//

#ifndef CORE_MESSAGING_PROJECT_SERVERCONFIGS_H
#define CORE_MESSAGING_PROJECT_SERVERCONFIGS_H

#include <iostream>
#include <fstream>
#include <map>
#include <nlohmann/json.hpp>
#include <vector>

class ServerConfig {
public:
    ServerConfig(std::string t_configPath) : m_serverConfigPath(t_configPath) {
        nlohmann::json data = getServerConfigs();
        m_serverPort = data["server"]["port"];
        m_mongoPath  = data["server"]["dbConnection"];
        m_logPath    = data["server"]["logPath"];
        setRouteConfig(data);
    }

    const std::string &getServerPort() const {
        return m_serverPort;
    }

    const std::string &getMongoPath() const {
        return m_mongoPath;
    }

    const std::string &getLogPath() const {
        return m_logPath;
    }

    const std::map<std::string, std::string> &getRouteConfig() const {
        return m_routeConfig;
    }
private:
    std::string m_serverConfigPath;
    std::string m_serverPort;
    std::string m_mongoPath;
    std::string m_logPath;
    std::map<std::string, std::string> m_routeConfig;

    nlohmann::json getServerConfigs();
    void setRouteConfig(nlohmann::json m_data);
};

#endif //CORE_MESSAGING_PROJECT_SERVERCONFIGS_H
