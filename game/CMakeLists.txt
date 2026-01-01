add_executable(Splatform
        main.cpp
        src/ObjectSpawnList.cpp
        src/SceneCamera.cpp
        src/TestScript.cpp
        src/WorldMap.cpp
        include/TerrainTile.h
        src/TerrainTile.cpp
        include/Settlement.h
        src/Settlement.cpp
        include/GameManager.h
        include/SettlerManager.h
        src/GameManager.cpp
        src/SettlerManager.cpp
        include/GameSettings.h
        include/UI/ScreenspaceButton.h
        src/UI/ScreenspaceButton.cpp
        include/UI/GameSpeedUI.h
        src/UI/GameSpeedUI.cpp
        include/CollisionTests/CollisionTests.h
        src/CollisionTests/CollisionTests.cpp
        include/CollisionTests/ColliderDebug.h
        src/CollisionTests/ColliderDebug.cpp
        include/CollisionTests/AABBTestClass.h
        src/AABBTestClass.cpp
)

target_link_libraries(Splatform PRIVATE Engine)

target_include_directories(Splatform PRIVATE
        ${PROJECT_SOURCE_DIR}/engine/include
        ${PROJECT_SOURCE_DIR}/game/include
)
if(WIN32)
    add_custom_command(TARGET Splatform POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_BINARY_DIR}/engine/libEngine.dll
            $<TARGET_FILE_DIR:Platformer>
    )
    add_custom_command(TARGET Splatform POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E echo "Copying bin files from ${PROJECT_SOURCE_DIR}/bin to $<TARGET_FILE_DIR:Splatform>"
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${PROJECT_SOURCE_DIR}/bin
            $<TARGET_FILE_DIR:Splatform>
    )
endif(WIN32)

add_custom_command(TARGET Splatform POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Copying assets from ${PROJECT_SOURCE_DIR}/assets to $<TARGET_FILE_DIR:Splatform>/assets"
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:Splatform>/assets
)
message("ENGINE INCLUDE PATH: ${PROJECT_SOURCE_DIR}/engine/include")
message("Assets INCLUDE PATH: ${PROJECT_SOURCE_DIR}/assets")