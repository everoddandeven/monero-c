cmake_minimum_required(VERSION 3.20)

if (WIN32)
  add_definitions( "-D_GLIBCXX_USE_NANOSLEEP=1" )
  add_definitions( "-DWIN32_LEAN_AND_MEAN" )
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wa,-mbig-obj -O2 -fPIC -std=c++14 -F/Library/Frameworks -pthread -lcrypto -lcrypt32 -lbcrypt") 
else()
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -std=c++14 -F/Library/Frameworks -pthread")
endif()

project(monero-c VERSION 1.0 LANGUAGES CXX)

#############
# System
#############

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# TODO: remove TRUEs, how are APPLE, DEPENDS, etc initialized?
if (TRUE OR HIDAPI_FOUND OR LibUSB_COMPILE_TEST_PASSED)
  if (APPLE)
    if(TRUE OR DEPENDS)
      list(APPEND EXTRA_LIBRARIES "-framework Foundation -framework IOKit -framework AppKit")
    else()
      find_library(COREFOUNDATION CoreFoundation)
      find_library(IOKIT IOKit)
      find_library(APPKIT AppKit)
      list(APPEND EXTRA_LIBRARIES ${IOKIT})
      list(APPEND EXTRA_LIBRARIES ${COREFOUNDATION})
      list(APPEND EXTRA_LIBRARIES ${APPKIT})
    endif()
  endif()
  if (WIN32)
    list(APPEND EXTRA_LIBRARIES setupapi)
  endif()
endif()

message(STATUS EXTRA_LIBRARIES: ${EXTRA_LIBRARIES})

############
# Boost
############

set(Boost_NO_BOOST_CMAKE 1)
set(Boost_USE_MULTITHREADED ON)
set(BOOST_COMPONENTS chrono date_time filesystem program_options serialization wserialization thread)

# Find Boost headers
set(BOOST_MIN_VER 1.62)
find_package(Boost ${BOOST_MIN_VER} QUIET REQUIRED)

# Boost System is header-only since 1.69
if (Boost_VERSION_STRING VERSION_LESS 1.69.0)
  list(APPEND BOOST_COMPONENTS system)
endif()

# Boost Regex is header-only since 1.77
if (Boost_VERSION_STRING VERSION_LESS 1.77.0)
  list(APPEND BOOST_COMPONENTS regex)
endif()

find_package(Boost ${BOOST_MIN_VER} QUIET REQUIRED COMPONENTS ${BOOST_COMPONENTS})
message(STATUS "Boost components: ${BOOST_COMPONENTS}")
message(STATUS "Using Boost include dir at ${Boost_INCLUDE_DIR}")

############
# OpenSSL
############

if (APPLE AND NOT IOS)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=default -std=c++14")
  if (NOT OPENSSL_ROOT_DIR)
      EXECUTE_PROCESS(COMMAND brew --prefix openssl
        OUTPUT_VARIABLE OPENSSL_ROOT_DIR
        OUTPUT_STRIP_TRAILING_WHITESPACE)
    message(STATUS "Using OpenSSL found at ${OPENSSL_ROOT_DIR}")
  endif()
endif()

find_package(OpenSSL REQUIRED)
message(STATUS "Using OpenSSL include dir at ${OPENSSL_INCLUDE_DIR}")

if(STATIC AND NOT IOS)
  if(UNIX)
    set(OPENSSL_LIBRARIES "${OPENSSL_LIBRARIES};${CMAKE_DL_LIBS};${CMAKE_THREAD_LIBS_INIT}")
  endif()
endif()

if (WIN32)
  list(APPEND OPENSSL_LIBRARIES ws2_32 crypt32 bcrypt)
endif()

###################
# monero-cpp
###################

set(MONERO_CPP "${CMAKE_SOURCE_DIR}/external/monero-cpp")
set(MONERO_CPP_BUILD "${MONERO_CPP}/build" CACHE STRING "Monero C++ build directory")
set(MONERO_PROJECT ${MONERO_CPP}/external/monero-project)
message(STATUS "Using monero-cpp build: " ${MONERO_CPP_BUILD})

add_library(monero-cpp SHARED IMPORTED)

if (APPLE)
  set_target_properties(monero-cpp PROPERTIES IMPORTED_LOCATION
      ${MONERO_CPP_BUILD}/libmonero-cpp.dylib)
elseif (WIN32)
  set_target_properties(monero-cpp PROPERTIES IMPORTED_LOCATION
      ${MONERO_CPP_BUILD}/libmonero-cpp.dll)
  set_target_properties(monero-cpp PROPERTIES IMPORTED_IMPLIB
      ${MONERO_CPP_BUILD}/libmonero-cpp.dll.a)
else()
  set_target_properties(monero-cpp PROPERTIES IMPORTED_LOCATION
      ${MONERO_CPP_BUILD}/libmonero-cpp.so)
endif()

###############################################
# Build dynamic library
###############################################

set(
    MONERO_C_FILES
    src/monero_api_c.cpp
)
add_library(monero-c SHARED ${MONERO_C_FILES})

target_include_directories(monero-c PRIVATE
    src
    ${MONERO_CPP}/src
    ${MONERO_PROJECT}/src
    ${MONERO_PROJECT}/contrib/epee/include
    ${MONERO_PROJECT}/external
    ${MONERO_PROJECT}/external/easylogging++
    ${MONERO_PROJECT}/external/rapidjson/include
    ${Boost_INCLUDE_DIR}
    ${OPENSSL_INCLUDE_DIR}
)

target_link_libraries(monero-c PRIVATE
    monero-cpp

    ${Boost_LIBRARIES}
    ${OPENSSL_LIBRARIES}
    ${EXTRA_LIBRARIES}
)

if (WIN32)
  target_link_options(monero-c PUBLIC "-Wl,--enable-auto-import,--export-all-symbols")
endif()

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_link_options(monero-c PRIVATE "-z" "noexecstack")
endif()

INSTALL(FILES src/monero_api_c.h
        DESTINATION include)
INSTALL(TARGETS monero-c
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT Runtime
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT Runtime
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT Development)

# search for libmonero-cpp.dylib in same directory as libmonero-c.dylib on mac for portability
# command: install_name_tool -add_rpath @loader_path/ ./libmonero-c.dylib 
if (APPLE)
    add_custom_command(TARGET monero-c 
        POST_BUILD COMMAND 
        ${CMAKE_INSTALL_NAME_TOOL} -add_rpath "@loader_path/"
        $<TARGET_FILE:monero-c>)
endif()
