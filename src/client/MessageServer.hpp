//
// Created by Leo on 17/12/19.
//

#ifndef CORE_MESSAGESERVER_HPP
#define CORE_MESSAGESERVER_HPP

#include <zmq.hpp>
#include <thread>

#include "../config/LogConfig.hpp"

class MessageServer {
public:
    MessageServer(const std::string& t_port, zmq::context_t t_context, zmq::socket_type t_socket)
        :  m_port(t_port),
        m_context(static_cast<zmq::context_t &&>(t_context)),
        m_socket(zmq::socket_t(m_context, t_socket)) { }

    void startThread() {
        m_thread = std::thread(&MessageServer::openPort, this);
    }

    void stopThread() {
        m_socket.close();
        m_running = false;
    }

    void join() {
        m_thread.join();
    }

    virtual void openPort() = 0;

protected:
    bool m_running = false;
    LogConfig m_log;
    zmq::context_t m_context;
    zmq::socket_t m_socket;
    std::thread m_thread;
    std::string m_port;

};

#endif //CORE_MESSAGESERVER_HPP
