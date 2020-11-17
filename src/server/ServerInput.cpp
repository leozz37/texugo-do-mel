//
// Created by Leo on 03/12/19.
//

#include "ServerInput.hpp"
#include "../config/PayloadConfig.hpp"

ServerInput::ServerInput(const std::string t_port, std::vector<std::unique_ptr<ClientPub>>& t_clients, DatabaseDao& t_db)
        : MessageServer(t_port, (zmq::context_t)1, (zmq::socket_type)ZMQ_REP),
        m_clients(t_clients), m_db(t_db){
}

void ServerInput::openPort() {
    m_socket.bind("tcp://*:" + m_port);
    m_log.logInfo("INPUT THREAD STARTED SUCCESSFULLY");
    m_running = true;

    while (m_running) {
        zmq::message_t request;

        zmq::detail::recv_result_t ret = m_socket.recv(request, zmq::recv_flags::dontwait);
        if(!ret.has_value()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            continue;
        }

        std::string message = std::string(static_cast<char *>(request.data()), request.size());
        PayloadConfig payload(message);
        m_log.logWarn("Message received from: " + payload.getOriginator());
        inputQueue(payload);
        m_db.insertDb(payload);

        zmq::message_t reply(2);
        memcpy(reply.data(), "OK", 2);
        m_socket.send(reply, zmq::send_flags::none);
    }

    m_log.logWarn("INPUT THREAD STOPPED");
}

void ServerInput::inputQueue(const PayloadConfig& payload) {
    for (auto& element : payload.getRecipient()) {
        short pos = handleDestination(element);

        if (pos == -1) {
            m_log.logWarn("RECIPIENT DOESN'T EXISTS: " + element);
            continue;
        }

        std::string content = payload.getContent();
        m_clients[pos]->inputQueue(content);
    }
}

short ServerInput::handleDestination(const std::string t_recipient) {
    for (int i = 0; i < m_clients.size(); i++) {
        if (m_clients[i]->getId() == t_recipient) {
            return i;
        }
    }
    return -1;
}

