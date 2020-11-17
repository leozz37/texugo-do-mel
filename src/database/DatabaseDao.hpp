//
// Created by Leo on 08/01/20.
//

#ifndef CORE_DATABASEDAO_HPP
#define CORE_DATABASEDAO_HPP

#include "DatabaseDao.hpp"
#include "../config/PayloadConfig.hpp"
#include "../config/ServerConfig.hpp"
#include <cstdint>
#include <iostream>
#include <vector>
#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/array.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>
#include <string>

class DatabaseDao {
public:
    DatabaseDao(ServerConfig &t_ServerConfigs);
    void insertDb(PayloadConfig payload);
private:
    bsoncxx::document::value parseDocument(PayloadConfig payload);
    ServerConfig &m_serverConfig;
    mongocxx::instance inst;
};


#endif //CORE_DATABASEDAO_HPP
