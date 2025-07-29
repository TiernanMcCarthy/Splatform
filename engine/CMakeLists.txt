file(GLOB_RECURSE ENGINE_SOURCES src/*.cpp)
file(GLOB_RECURSE ENGINE_HEADERS include/*.h)

add_library(Engine SHARED
        ${ENGINE_SOURCES}
        ${ENGINE_HEADERS}
        include/StartupSequence.h
        src/StartupSequence.cpp
        src/Button.cpp
        include/FunctionSubscriber.h
        src/FunctionSubscriber.cpp
        include/CameraView.h
        include/Systems/ThreadPool.h
        src/Systems/Threadpool.cpp
)



target_include_directories(Engine PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(Engine
        sfml-graphics
        sfml-window
        sfml-audio
        sfml-system
)

target_compile_definitions(Engine PRIVATE ENGINE_EXPORTS)
