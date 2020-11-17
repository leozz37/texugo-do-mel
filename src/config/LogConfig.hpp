//
// Created by Leo on 16/12/19.
//

#ifndef CORE_LOGCONFIG_HPP
#define CORE_LOGCONFIG_HPP

#include <string>
#include <spdlog/spdlog.h>

#include "spdlog/sinks/rotating_file_sink.h"

class LogConfig {
public:
    void openLogFile(ServerConfig config){
        std::string logPath = config.getLogPath();
        auto logFile = spdlog::rotating_logger_mt("logFile", logPath, 1048576 * 5, 3);
        logFile->info("Log file opened");
    }

    void logInfo(std::string message) {
        spdlog::info(message);
        spdlog::get("logFile")->info(message);
    }

    void logWarn(std::string message) {
        spdlog::warn(message);
        spdlog::get("logFile")->warn(message);
    }

    void logCritical(std::string message) {
        spdlog::critical(message);
        spdlog::get("logFile")->critical(message);
    }

    void logInfoStar(std::string message) {
        spdlog::info("***********************************");
        spdlog::info(message);
        spdlog::info("***********************************");
        spdlog::get("logFile")->info(message);
    }

    void logInfoSlash(std::string message) {
        spdlog::info("-----------------------------------");
        spdlog::info(message);
        spdlog::info("-----------------------------------");
        spdlog::get("logFile")->info(message);
    }
};

#endif //CORE_LOGCONFIG_HPP
