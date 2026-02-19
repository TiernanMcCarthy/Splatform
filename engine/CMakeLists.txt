file(GLOB_RECURSE ENGINE_SOURCES src/*.cpp)
file(GLOB_RECURSE ENGINE_HEADERS include/*.h)

add_library(Engine SHARED
        ${ENGINE_SOURCES}
        ${ENGINE_HEADERS}
        include/Objects/EntityID.h
        include/StartupSequence.h
        src/StartupSequence.cpp
        src/UI/Button.cpp
        include/Systems/FunctionSubscriber.h
        src/Systems/FunctionSubscriber.cpp
        include/Systems/ThreadPool.h
        src/Systems/Threadpool.cpp
        include/Systems/FastCommonExtensions.h
        include/AABB.h
        src/AABB.cpp
        src/Collider.cpp
        include/Gizmos/GizmoManager.h
        src/Gizmos/GizmoManager.cpp
        include/Serialization/Serializer.h
        src/Serialization/Serializer.cpp
        include/Scenes/SceneManager.h
        include/Scenes/Scene.h
        src/Scenes/SceneManager.cpp
        src/Scenes/Scene.cpp
        include/Terrain/BuildingBlocks/RectangleBlock.h
        src/Terrain/BuildingBlocks/RectangleBlock.cpp

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
target_include_directories(Engine PUBLIC "${CMAKE_BINARY_DIR}/generated")

target_compile_definitions(Engine PRIVATE ENGINE_EXPORTS)