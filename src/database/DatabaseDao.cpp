//
// Created by Leo on 08/01/20.
//

#include "DatabaseDao.hpp"
#include "../config/PayloadConfig.hpp"
#include "../config/ServerConfig.hpp"

#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <ctime>
#include <mongocxx/client.hpp>
#include <mongocxx/uri.hpp>

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;

void DatabaseDao::insertDb(PayloadConfig payload) {
    bsoncxx::document::value doc = parseDocument(payload);
    bsoncxx::document::view view = doc.view();
    mongocxx::client conn{mongocxx::uri{m_serverConfig.getMongoPath()}};
    mongocxx::database db = conn["core-messaging"];
    mongocxx::collection coll = db["payload"];
    bsoncxx::stdx::optional<mongocxx::result::insert_one> result =
            coll.insert_one(view);
}

bsoncxx::document::value DatabaseDao::parseDocument(PayloadConfig payload) {
    std::time_t rawtime;
    time(&rawtime);

    document dataBuilder{};
    auto arrayBuilder = dataBuilder
            << "payload" << open_document
            << "recipient" << open_array;
            for (auto& i : payload.getRecipient()) {
                arrayBuilder << i;
            }
            arrayBuilder << close_array;
            dataBuilder << "originator" << payload.getOriginator();
            dataBuilder << "content" << payload.getContent();
            dataBuilder << "time" <<  ctime (&rawtime);
            dataBuilder << close_document;
            bsoncxx::document::value doc = dataBuilder << finalize;
    return doc;
}

DatabaseDao::DatabaseDao(ServerConfig &t_serverConfig) : m_serverConfig(t_serverConfig) {}

