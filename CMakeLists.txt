cmake_minimum_required(VERSION 3.10)

#vcpkg

if(NOT DEFINED VCPKG_ROOT)
    set(VCPKG_ROOT "C:/Users/arsbo/vcpkg")
endif()

set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")

##############

project(my_project)

###############
#find packages
find_package(SFML 2.5.1 COMPONENTS system window graphics audio REQUIRED)

# Sources include
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake_scripts/cmake_scripts.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/sources/sources.cmake)
get_sources(SOURCES_LIST ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
###############

add_executable(${PROJECT_NAME}  ${SOURCES_LIST})

#target
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/sources)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system sfml-audio sfml-network sfml-graphics sfml-window)



