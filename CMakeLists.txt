cmake_minimum_required(VERSION 3.5)

project(signal-translator VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(sdbus-c++)

set(PROJECT_SOURCES
        main.cpp
        dbusListener.cpp
        dbusListener.h
        logger.h
        logger.cpp
)

add_executable(signal-translator
    ${PROJECT_SOURCES}
)

install(TARGETS signal-translator
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

target_link_libraries(signal-translator PRIVATE SDBusCpp::sdbus-c++)
