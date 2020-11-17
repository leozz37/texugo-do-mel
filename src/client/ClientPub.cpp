//
// Created by Leo on 03/12/19.
//

#include "ClientPub.hpp"
#include "spdlog/spdlog.h"

#include <zmq.hpp>

ClientPub::ClientPub(const std::string t_id, const std::string t_port)
        : m_id(t_id), MessageServer(t_port, (zmq::context_t) 1, (zmq::socket_type) ZMQ_PUB) {
}

void ClientPub::openPort() {
    m_socket.bind("tcp://*:" + m_port);
    m_log.logInfo("THREAD " + m_id + " STARTED SUCCESSFULLY");
    m_running = true;

    while(m_running) {
        if(!m_queue.empty()) {
            std::string& content = m_queue.front();
            zmq::message_t message(content.data(), content.size());
            m_socket.send(message, zmq::send_flags::none);
            m_queue.pop();
            m_log.logInfo("Message delivered to:  " + m_id);
        }
    }
    m_log.logCritical("CLIENT THREAD " + m_id + " STOPPED");
}

void ClientPub::inputQueue(std::string t_message) {
    m_queue.push(t_message);
}

const std::string &ClientPub::getId() const {
    return m_id;
}
