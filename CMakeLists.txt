cmake_minimum_required(VERSION 3.10)

# ---------------- SETUP ----------------

enable_language(CXX)
set(CMAKE_CXX_COMPILER ${CONAN_CXX_COMPILER})
set(CMAKE_CXX_STANDARD 20)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

link_directories(${CONAN_LIB_DIRS})

# ---------------- Client ----------------

project(r-type_client
        VERSION 0.1.0
        LANGUAGES CXX)

set(SRCS
        Client/src/main.cpp
        Client/src/client.cpp
        Client/src/screen.cpp
        Client/src/entityHandler.cpp
        Client/src/vectors.cpp
        Client/src/soundManager.cpp)

set(HEADERS
        Client/include/client.hpp
        Client/include/screen.hpp
        Client/include/vector.hpp
        Client/include/soundManager.hpp)

add_executable(r-type_client ${SRCS} ${HEADERS})

target_link_libraries(r-type_client
        ${CONAN_LIBS}
        rtype-network
        rtype-gameengine
        )

target_include_directories(r-type_client PUBLIC
        Client/include
        Lib/Network/include
        ${CONAN_INCLUDE_DIRS_RAYLIB}
        )
# ---------------- Server ----------------

project(r-type_server
        VERSION 0.1.0
        LANGUAGES CXX)

set(SRC_SERVER
        Server/src/main.cpp
        Server/src/Lobby.cpp
        Server/src/Clock.cpp
        Server/src/Entities/Enemy.cpp
        Server/src/Entities/Player.cpp
        Server/src/Entities/Rocket.cpp
        Server/src/Entities/PowerUp.cpp
        Server/src/Entities/Wall.cpp
        Server/src/utils/utils.cpp
        Server/src/utils/unloadId.cpp
        Server/src/utils/sendWaveNumber.cpp
        Server/src/ManageLobby.cpp
        )

set(HEADERS_SERVER
        Server/include/Clock.hpp
        Server/include/Lobby.hpp
        Server/include/Entities/Enemy.hpp
        Server/include/Entities/IEntity.hpp
        Server/include/Entities/Player.hpp
        Server/include/Entities/PowerUp.hpp
        Server/include/Entities/Rocket.hpp
        Server/include/utils/utils.hpp
	Server/include/utils/shutdown.hpp
        Server/include/utils/unloadId.hpp
        Server/include/utils/sendWaveNumber.hpp
        Server/include/ManageLobby.hpp
        )

add_executable(r-type_server ${SRC_SERVER} ${HEADERS_SERVER})

target_link_libraries(r-type_server
        ${CONAN_LIBS}
        rtype-gameengine
        )

target_include_directories(r-type_server PUBLIC
        Server/include
        Lib/Network/include
        ${CONAN_INCLUDE_DIRS_RAYLIB}
        )

# ---------------- Network ----------------

set(SRC_NETWORK
        Lib/Network/src/error.cpp
        )

set(HEADERS_NETWORK
        Lib/Network/include/client_interface.hpp
        Lib/Network/include/connection_type.hpp
        Lib/Network/include/connection.hpp
        Lib/Network/include/error.hpp
        Lib/Network/include/message.hpp
        Lib/Network/include/safe_queue.hpp
        Lib/Network/include/server_interface.hpp
        )

add_library(rtype-network
        ${SRC_NETWORK}
        ${HEADERS_NETWORK}
        )

target_link_libraries(rtype-network
        ${CONAN_LIBS}
        )

target_include_directories(rtype-network PUBLIC
        ${CONAN_INCLUDE_DIRS_BOOST}
        )

# ---------------- GAME ENGINE ----------------

set(SRC_ENGINE
        Lib/GameEngine/src/Entity.cpp
        Lib/GameEngine/src/EntityManager.cpp
        Lib/GameEngine/src/Components/Component.cpp
        Lib/GameEngine/src/Components/Damages.cpp
        Lib/GameEngine/src/Components/Cooldown.cpp
        Lib/GameEngine/src/Components/Friendly.cpp
        Lib/GameEngine/src/Components/Health.cpp
        Lib/GameEngine/src/Components/Hitbox.cpp
        Lib/GameEngine/src/Components/Position.cpp
        Lib/GameEngine/src/Components/Score.cpp
        Lib/GameEngine/src/Components/Speed.cpp
        Lib/GameEngine/src/Components/Speed.cpp
        Lib/GameEngine/src/Components/Style.cpp
        Lib/GameEngine/src/Utils/Background.cpp
        Lib/GameEngine/src/Utils/Button.cpp
        Lib/GameEngine/src/Utils/Sprite.cpp
        Lib/GameEngine/src/Utils/Text.cpp
        Lib/GameEngine/src/Utils/Musics.cpp
        Lib/GameEngine/src/Utils/Sounds.cpp
        )

set(HEADERS_ENGINE
        Lib/GameEngine/include/Constants.hpp
        Lib/GameEngine/include/Components/Component.hpp
        Lib/GameEngine/include/Components/Cooldown.hpp
        Lib/GameEngine/include/Components/Damages.hpp
        Lib/GameEngine/include/Components/Friendly.hpp
        Lib/GameEngine/include/Components/Health.hpp
        Lib/GameEngine/include/Components/Hitbox.hpp
        Lib/GameEngine/include/Components/IComponent.hpp
        Lib/GameEngine/include/Components/Position.hpp
        Lib/GameEngine/include/Components/Score.hpp
        Lib/GameEngine/include/Components/Speed.hpp
        Lib/GameEngine/include/Components/Style.hpp
        Lib/GameEngine/include/Entity/Entity.hpp
        Lib/GameEngine/include/Entity/EntityManager.hpp
        Lib/GameEngine/include/Utils/Background.hpp
        Lib/GameEngine/include/Utils/Button.hpp
        Lib/GameEngine/include/Utils/Sprite.hpp
        Lib/GameEngine/include/Utils/Text.hpp
        Lib/GameEngine/include/Utils/Musics.hpp
        Lib/GameEngine/include/Utils/Sounds.hpp
        )

add_library(rtype-gameengine
        ${SRC_ENGINE}
        ${HEADERS_ENGINE}
        )

target_link_libraries(rtype-gameengine
        ${CONAN_LIBS}
        )

target_include_directories(rtype-gameengine PUBLIC
        ${CONAN_INCLUDE_DIRS_RAYLIB}
        ${CONAN_INCLUDE_DIRS_BOOST}
        )


message("Boost library: "${CONAN_INCLUDE_DIRS_BOOST})
# ---------------- BIN ----------------
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR})
install(TARGETS r-type_server r-type_client
        RUNTIME DESTINATION bin/)