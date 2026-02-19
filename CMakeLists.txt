cmake_minimum_required(VERSION 3.31)
project(Splatform)

set(CMAKE_CXX_STANDARD 17)
set(BUILD_SHARED_LIBS ON)
set(SFML_STATIC_LIBRARIES TRUE)

include(FetchContent)
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.0
)
FetchContent_MakeAvailable(SFML)

# Behaviour Registry for ensuring all required scripts are compiled and added to dlls
# Just because a built exe doesn't use them, doesn't mean a serialised scene wouldn't
find_package(Python3 REQUIRED)
set(GEN_HEADER_DIR "${CMAKE_BINARY_DIR}/generated")
set(GEN_HEADER "${GEN_HEADER_DIR}/GeneratedRegistry.h")

add_custom_command(
        OUTPUT "${GEN_HEADER}"
        COMMAND Python3::Interpreter "${CMAKE_SOURCE_DIR}/engine/enginescripts/generate_registry.py"
        "${GEN_HEADER}" "${CMAKE_SOURCE_DIR}/engine" "${CMAKE_SOURCE_DIR}/game"
        DEPENDS "${CMAKE_SOURCE_DIR}/engine/enginescripts/generate_registry.py"
        COMMENT "Scanning for Behaviours in Engine and Game folders..."
        VERBATIM
)

add_custom_target(GenerateRegistry DEPENDS "${GEN_HEADER}")
# ------------------------------------

add_subdirectory(engine)
add_subdirectory(game)
add_subdirectory(editor)

add_dependencies(Engine GenerateRegistry)
add_dependencies(GameLib GenerateRegistry)