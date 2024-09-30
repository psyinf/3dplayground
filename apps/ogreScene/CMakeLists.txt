cmake_minimum_required(VERSION 3.20)
project(ExampleProject)

# Find packages
find_package(OGRE REQUIRED COMPONENTS Bites CONFIG)
find_package(pugixml CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)

add_executable(${PROJECT_NAME} "PointSprites.cpp")

target_link_libraries(${PROJECT_NAME} PRIVATE 
    OgreMain 
    OgreBites 
    Codec_STBI 
    OgrePaging 
    OgreTerrain
    Plugin_DotScene
    RenderSystem_Direct3D11
    RenderSystem_GL3Plus
    Plugin_ParticleFX
    pugixml
    assimp::assimp
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()


# Copy all runtime DLLs
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}> ${CMAKE_INSTALL_PREFIX}/bin
    COMMAND_EXPAND_LISTS
)

# Copy Ogre plugins
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:Plugin_DotScene>
        $<TARGET_FILE:RenderSystem_Direct3D11>
        $<TARGET_FILE:RenderSystem_GL3Plus>
        $<TARGET_FILE:Plugin_ParticleFX>
        ${CMAKE_INSTALL_PREFIX}/bin
)


install(TARGETS ${PROJECT_NAME}
RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib

)

#config files
install(FILES ${CMAKE_SOURCE_DIR}/data/plugins.cfg DESTINATION bin)
install(FILES ${CMAKE_SOURCE_DIR}/data/resources.cfg DESTINATION bin)
#create bin folder
file(MAKE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin)
#HACK to get the ALL dlls
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/  DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
    FILES_MATCHING  PATTERN "*.dll" 
    PATTERN "CMakeFiles" EXCLUDE
)