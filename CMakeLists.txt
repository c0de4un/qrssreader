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
find_package(Qt5 COMPONENTS Core Quick Qml QuickControls2 Widgets Network Xml REQUIRED)
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
    "src/cpp/rss/Channel.hpp"
    "src/cpp/rss/Item.hpp"
    "src/cpp/rss/Integer.hpp"
    "src/cpp/rss/Enclosure.hpp"
    "src/cpp/rss/Text.hpp"
    "src/cpp/rss/Date.hpp"
    "src/cpp/rss/Link.hpp"
    "src/cpp/rss/Cloud.hpp"
    "src/cpp/rss/Source.hpp"
    "src/cpp/rss/Image.hpp"
    "src/cpp/rss/Element.hpp"
    "src/cpp/rss/ChannelModel.hpp"
    "src/cpp/rss/TextInput.hpp"
    # UI
    "src/cpp/ui/MainWindowLogic.hpp"
    # UTILS
    "src/cpp/utils/SAXRSSHandler.hpp"
    "src/cpp/utils/IDStorage.hpp"
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
    "src/cpp/rss/Channel.cpp"
    "src/cpp/rss/Item.cpp"
    "src/cpp/rss/Integer.cpp"
    "src/cpp/rss/Enclosure.cpp"
    "src/cpp/rss/Text.cpp"
    "src/cpp/rss/Date.cpp"
    "src/cpp/rss/Link.cpp"
    "src/cpp/rss/Cloud.cpp"
    "src/cpp/rss/Source.cpp"
    "src/cpp/rss/Image.cpp"
    "src/cpp/rss/Element.cpp"
    "src/cpp/rss/ChannelModel.cpp"
    "src/cpp/rss/TextInput.cpp"
    # UTILS
    "src/cpp/utils/SAXRSSHandler.cpp"
    # UI
    "src/cpp/ui/MainWindowLogic.cpp" )

# =================================================================================
# BUILD
# =================================================================================

# Create Executable Object
add_executable( ${PROJECT_NAME} ${QT_RSS_READER_PROJECT_SOURCES} ${QT_RSS_READER_PROJECT_HEADERS} )

# Configure Executable Object
set_target_properties ( ${PROJECT_NAME} PROPERTIES
#OUTPUT_NAME "${ROOT_PROJECT_NAME}_v${ROOT_PROJECT_VERSION}"
RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin" )

# Set Executable Object Definitions
target_compile_definitions( ${PROJECT_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG> )

# Link Executable Object
target_link_libraries( ${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Quick Qt5::QuickControls2 Qt5::Qml Qt5::Widgets  Qt5::Network Qt5::Xml )
