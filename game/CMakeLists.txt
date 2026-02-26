
#Game exists as a library now which is called by the Editor and the Splatform Executable in builds
add_library(GameLib SHARED
        src/ObjectSpawnList.cpp
        src/SceneCamera.cpp
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
        include/SceneLoadDummy.h
        src/SceneLoadDummy.cpp
        include/CollisionTests/LoadSaveTest.h
        include/CollisionTests/LoadUI.h
        src/CollisionTests/LoadUI.cpp
        include/TestPlayer/TestPlayer.h
        src/TestPlayer/TestPlayer.cpp
        include/TestPlayer/PlayerSpawn.h
        src/TestPlayer/PlayerSpawn.cpp
        include/TestPlayer/PlayerScenario.h
        src/TestPlayer/PlayerScenario.cpp
        include/TestPlayer/TestCollectable.h
        include/TestPlayer/PlayerHUD.h
        src/TestPlayer/TestCollectable.cpp
)

# Link GameLib to Engine
target_link_libraries(GameLib PUBLIC Engine)

# Expose headers for Editor
target_include_directories(GameLib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/engine/include
)

#Standalone executable for game build
add_executable(Splatform main.cpp)

# Link the executable to the Game Logic
target_link_libraries(Splatform PRIVATE GameLib)

#copy assets and dlls to correct folders, different requirements on Windows
if(WIN32)
    #engine DLL
    add_custom_command(TARGET Splatform POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:Engine>
            $<TARGET_FILE_DIR:Splatform>
    )
    #Game dll
    add_custom_command(TARGET Splatform POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:GameLib>
            $<TARGET_FILE_DIR:Splatform>
    )

    # Copy Binaries
    add_custom_command(TARGET Splatform POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E echo "Copying bin files..."
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${PROJECT_SOURCE_DIR}/bin
            $<TARGET_FILE_DIR:Splatform>
    )
endif(WIN32)

target_include_directories(GameLib PUBLIC "${CMAKE_BINARY_DIR}/generated")

# Copy Assets
add_custom_command(TARGET Splatform POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Copying assets..."
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:Splatform>/assets
)