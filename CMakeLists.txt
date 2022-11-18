project(SuperMario)

cmake_minimum_required(VERSION 3.24.2)

set(CMAKE_SKIP_BUILD_RPATH 0)
set(CMAKE_BUILD_WITH_INSTALL_RPATH 0)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH 1)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

find_package(SFML 2.5.1 COMPONENTS audio graphics window system REQUIRED)

add_subdirectory(Sources)
