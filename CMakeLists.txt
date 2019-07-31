# =================================================================================
# CMake Meta-Data
# =================================================================================

cmake_minimum_required(VERSION 3.1)

# =================================================================================
# PROJECT
# =================================================================================

project(QRssReader LANGUAGES CXX)

# =================================================================================
# OPTIONS
# =================================================================================

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# =================================================================================
# QT
# =================================================================================

# QT.Core
find_package(Qt5 COMPONENTS Core Quick Widgets REQUIRED)

# Detect DEBUG-Mode
if ( CMAKE_BUILD_TYPE STREQUAL "Debug" ) # DEBUG
    add_definitions( -DDEBUG=1 )
else ( CMAKE_BUILD_TYPE STREQUAL "Debug" ) # !DEBUG
endif ( CMAKE_BUILD_TYPE STREQUAL "Debug" )

# =================================================================================
# HEADERS
# =================================================================================

# Project Header-files.
set ( QT_RSS_READER_PROJECT_HEADERS
    # MAIN
    "main.hpp"
    # RSS
    "src/cpp/rss/ChannelModel.hpp"
    # UI
    "src/cpp/ui/MainWindowLogic.hpp"
    # QML Resources
    "qml.qrc" )

# =================================================================================
# SOURCES
# =================================================================================

# Project Source-files.
set ( QT_RSS_READER_PROJECT_SOURCES
    # MAIN
    "main.cpp"
    # RSS
    "src/cpp/rss/ChannelModel.cpp"
    # UI
    "src/cpp/ui/MainWindowLogic.cpp" )

# =================================================================================
# BUILD
# =================================================================================

# Create Executable Object
add_executable( ${PROJECT_NAME} ${QT_RSS_READER_PROJECT_SOURCES} ${QT_RSS_READER_PROJECT_HEADERS} )

# Set Executable Object Definitions
target_compile_definitions( ${PROJECT_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG> )

# Link Executable Object
target_link_libraries( ${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Quick Qt5::Widgets )
