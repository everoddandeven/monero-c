cmake_minimum_required(VERSION 3.20)
project(monero-c VERSION 1.0 LANGUAGES C CXX)

include(ExternalProject)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include_directories(
    ${PROJECT_SOURCE_DIR}/src/utils
    ${PROJECT_SOURCE_DIR}/src/daemon
    ${CMAKE_CURRENT_SOURCE_DIR}/external/monero-cpp/src
    ${CMAKE_CURRENT_SOURCE_DIR}/external/monero-cpp/external/monero-project/src
    ${CMAKE_CURRENT_SOURCE_DIR}/external/monero-cpp/external/monero-project/contrib/epee/include
    ${CMAKE_CURRENT_SOURCE_DIR}/external/monero-cpp/external/monero-project/external
    ${CMAKE_CURRENT_SOURCE_DIR}/external/monero-cpp/external/monero-project/external/easylogging++
    ${CMAKE_CURRENT_SOURCE_DIR}/external/monero-cpp/external/monero-project/external/rapidjson/include    
)

set(MONERO_PROJECT_DIR ${CMAKE_SOURCE_DIR}/external/monero-cpp/external/monero-project)

ExternalProject_Add(monero-project
    SOURCE_DIR ${MONERO_PROJECT_DIR}
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ${CMAKE_MAKE_PROGRAM} -C ${MONERO_PROJECT_DIR} release-static -j1
    INSTALL_COMMAND ""
)

set(MONERO_CPP_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/monero-cpp)
set(MONERO_CPP_BUILD_DIR ${MONERO_CPP_DIR}/build)

ExternalProject_Add(monero-cpp-build
    SOURCE_DIR ${MONERO_CPP_DIR}
    BINARY_DIR ${MONERO_CPP_BUILD_DIR}
    CONFIGURE_COMMAND ${CMAKE_COMMAND} -S ${MONERO_CPP_DIR} -B ${MONERO_CPP_BUILD_DIR}
    BUILD_COMMAND ${CMAKE_COMMAND} --build ${MONERO_CPP_BUILD_DIR} -- -j$(nproc)
    INSTALL_COMMAND ""
    BUILD_BYPRODUCTS ${MONERO_CPP_BUILD_DIR}/libmonero-cpp.so
    DEPENDS monero-project
)

add_library(monero-cpp SHARED IMPORTED)
set_target_properties(monero-cpp PROPERTIES
    IMPORTED_LOCATION ${MONERO_CPP_BUILD_DIR}/libmonero-cpp.so
)

set(SOURCES
    src/utils/monero_utils_bridge.cpp
)

add_library(monero-c SHARED ${SOURCES})

add_dependencies(monero-c monero-cpp-build)

target_include_directories(monero-c
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/src/utils
        ${PROJECT_SOURCE_DIR}/src/daemon
)

target_link_libraries(monero-c
    PRIVATE 
        monero-cpp
)

if(WIN32)
    target_compile_definitions(monero-c PRIVATE monero_c_EXPORTS)
endif()

enable_testing()

find_package(PkgConfig REQUIRED)
pkg_check_modules(CHECK REQUIRED check)

add_executable(test_monero_utils test/test_monero_utils.c)
target_include_directories(test_monero_utils PRIVATE ${CHECK_INCLUDE_DIRS})
target_link_libraries(test_monero_utils PRIVATE monero-c ${CHECK_LIBRARIES})
add_test(NAME test_monero_utils COMMAND test_monero_utils)

