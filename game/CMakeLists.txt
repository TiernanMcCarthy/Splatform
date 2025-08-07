add_executable(CellularMap
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
)

target_link_libraries(CellularMap PRIVATE Engine)

target_include_directories(CellularMap PRIVATE
        ${PROJECT_SOURCE_DIR}/engine/include
        ${PROJECT_SOURCE_DIR}/game/include
)
if(WIN32)
add_custom_command(TARGET CellularMap POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/engine/libEngine.dll
        $<TARGET_FILE_DIR:CellularMap>
)
add_custom_command(TARGET CellularMap POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Copying lib files from ${PROJECT_SOURCE_DIR}/lib to $<TARGET_FILE_DIR:CellularMap>"
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/lib
        $<TARGET_FILE_DIR:CellularMap>
)
endif(WIN32)

add_custom_command(TARGET CellularMap POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Copying assets from ${PROJECT_SOURCE_DIR}/assets to $<TARGET_FILE_DIR:CellularMap>/assets"
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:CellularMap>/assets
)
message("ENGINE INCLUDE PATH: ${PROJECT_SOURCE_DIR}/engine/include")
message("Assets INCLUDE PATH: ${PROJECT_SOURCE_DIR}/assets")
