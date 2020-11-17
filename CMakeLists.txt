cmake_minimum_required(VERSION 3.0)
project(core)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

find_package(cppzmq REQUIRED)
find_package(nlohmann_json 3.2.0 REQUIRED)
find_package(spdlog REQUIRED)
find_package(libmongocxx REQUIRED)
find_package(libbsoncxx REQUIRED)

include_directories(${LIBMONGOCXX_INCLUDE_DIRS})
include_directories(${LIBBSONCXX_INCLUDE_DIRS})

add_executable(core-messaging src/main.cpp
        src/config/ServerConfig.hpp
        src/server/Server.hpp
        src/server/Server.cpp
        src/server/ServerInput.cpp
        src/server/ServerInput.hpp
        src/client/ClientPub.cpp
        src/client/ClientPub.hpp
        src/config/LogConfig.hpp
        src/client/MessageServer.hpp
        src/config/ServerConfig.cpp
        src/config/PayloadConfig.hpp src/database/DatabaseDao.cpp src/database/DatabaseDao.hpp)

target_link_libraries(
        core-messaging nlohmann_json::nlohmann_json
        cppzmq
        spdlog::spdlog
        ${LIBMONGOCXX_LIBRARIES}
        ${LIBBSONCXX_LIBRARIES})
