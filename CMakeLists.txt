cmake_minimum_required(VERSION 3.19)
set (CMAKE_CXX_STANDARD 17)
set(PROJ_NAME celer3d)
project(${PROJ_NAME}
    LANGUAGES CXX
)
message(${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB_RECURSE SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)
add_library(${PROJ_NAME} STATIC ${SRC})
target_include_directories(${PROJ_NAME} PUBLIC src)
find_package(Vulkan REQUIRED)
target_link_libraries(${PROJ_NAME} PUBLIC Vulkan::Vulkan)
add_subdirectory(external/spdlog ${CMAKE_CURRENT_BINARY_DIR}/spdlog)
target_link_libraries(${PROJ_NAME} PRIVATE spdlog)
add_subdirectory(external/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)
target_link_libraries(${PROJ_NAME} PUBLIC Vulkan::Vulkan glfw)