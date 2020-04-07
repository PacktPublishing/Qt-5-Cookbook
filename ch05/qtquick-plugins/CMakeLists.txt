cmake_minimum_required(VERSION 3.0)

project(qtquickapp)

include(GenerateExportHeader)
include(FeatureSummary)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

include_directories(${qtquickapp_SOURCE_DIR}/src/ ${qtquickapp_BINARY_DIR}/src/)

find_package(Qt5 CONFIG REQUIRED COMPONENTS
   Core
   Gui
   Qml
)

add_subdirectory(src)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
