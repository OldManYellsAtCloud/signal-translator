cmake_minimum_required(VERSION 3.5)

project(signal-translator VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(sdbus-c++)
find_package(loglib REQUIRED)
find_package(SettingsLib)

set(PROJECT_SOURCES
        src/main.cpp
        src/commandexecutor.cpp
        include/commandexecutor.h
)

add_executable(signal-translator
    ${PROJECT_SOURCES}
)

target_include_directories(signal-translator PUBLIC ${CMAKE_SOURCE_DIR}/include)

install(TARGETS signal-translator
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

target_link_libraries(signal-translator PRIVATE SDBusCpp::sdbus-c++ loglib SettingsLib)
