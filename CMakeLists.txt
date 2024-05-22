cmake_minimum_required(VERSION 3.15)
project(daagudumoothalu VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_INSTALL_DIR share/${PROJECT_NAME}/cmake)

find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
find_package(SDL2 REQUIRED CONFIG COMPONENTS SDL2main)

include_directories(
  ${CMAKE_SOURCE_DIR}/include
  ${SDL2_INCLUDE_DIRS}
)

# add libraries
# add_library(sdl_st SHARED
#   src/glfwindow.cpp
#   src/vulkan.cpp
# )

# target_link_libraries(glf_vulkan
#   ${Vulkan_LIBRARIES}
#   glfw
# )

# add_library(math SHARED
#   src/math.cpp
# )
# target_link_libraries(math

# )


# add_dependencies(XXXX)

add_executable(${PROJECT_NAME}
  src/sdl_stuff.c
  src/wumpus.c
  src/main.c
)

if(TARGET SDL2::SDL2main)
  target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2main)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
  SDL2::SDL2
)

# install
install(
  TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}-targets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
)

# Generate the CMake config file
include(CMakePackageConfigHelpers)
# Generate the version file accompanying the project's config file
configure_package_config_file(${PROJECT_NAME}-config.cmake.in
                              ${PROJECT_NAME}-config.cmake
                              INSTALL_DESTINATION ${CMAKE_INSTALL_DIR})

write_basic_package_version_file(${PROJECT_NAME}-config-version.cmake
                                 VERSION ${PROJECT_VERSION}
                                 COMPATIBILITY AnyNewerVersion)

# Install the config and configversion
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
        DESTINATION ${CMAKE_INSTALL_DIR})

# Make the targets accessible from this packages's build tree
export(
  EXPORT ${PROJECT_NAME}-targets
  NAMESPACE ${PROJECT_NAME}::
  FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-targets.cmake"
)

# Make the targets accessible from this packages's install tree
install(
  EXPORT ${PROJECT_NAME}-targets
  FILE ${PROJECT_NAME}-targets.cmake
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION ${CMAKE_INSTALL_DIR})

# Install all public header files
install(DIRECTORY include/
  DESTINATION include
  FILES_MATCHING PATTERN "*.h"
)

install(DIRECTORY assets/ 
  DESTINATION assets
)