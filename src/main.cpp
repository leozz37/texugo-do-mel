#include <csignal>
#include "server/Server.hpp"

Server server;

void signalHandling(int signalNum) {
    server.stop();
}

int main(int argc, char** argv) {
    if (argc != 2) {
        return 0;
    }
    std::string configPath(argv[1]);
    signal(SIGINT, signalHandling);
    ServerConfig config(configPath);
    server.init(config);
    return 0;
}