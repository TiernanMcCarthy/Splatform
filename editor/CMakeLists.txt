file(GLOB_RECURSE EDITOR_SOURCES src/*.cpp)
file(GLOB_RECURSE EDITOR_HEADERS include/*.h)


add_executable(Editor
        ${EDITOR_SOURCES}
        ${EDITOR_HEADERS}
        main.cpp
        include/Editor.h
        src/Editor.cpp
        include/TempEditor/SimpleMapEditor.h
        src/TempEditor/SimpleMapEditor.cpp
        include/TempEditor/EditorStartup.h
        src/TempEditor/EditorStartup.cpp

)

target_include_directories(Editor PRIVATE "${CMAKE_BINARY_DIR}/generated")

target_include_directories(Editor PRIVATE include)

# Link to Game Lib
target_link_libraries(Editor PRIVATE GameLib)


#Move required dlls to editor location
if(WIN32)
    # Copy Engine DLL
    add_custom_command(TARGET Editor POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:Engine>
            $<TARGET_FILE_DIR:Editor>
    )
    # Copy GameLib DLL
    add_custom_command(TARGET Editor POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:GameLib>
            $<TARGET_FILE_DIR:Editor>
    )
    # Copy SFML DLLs from bin
    add_custom_command(TARGET Editor POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E echo "Copying binaries to Editor, if they're not here, grab from the deps (I'm lazy and mostly use linux now anyway :))"
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${PROJECT_SOURCE_DIR}/bin
            $<TARGET_FILE_DIR:Editor>)
endif(WIN32)

# Copy Assets to Editor build folder
add_custom_command(TARGET Editor POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Copying assets to Editor..."
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:Editor>/assets
)