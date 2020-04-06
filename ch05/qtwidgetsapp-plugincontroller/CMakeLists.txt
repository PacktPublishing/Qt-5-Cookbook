cmake_minimum_required(VERSION 3.0)

project(qtwidgetsapp)

include(GenerateExportHeader)
include(FeatureSummary)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

include_directories(${qtwidgetsapp_SOURCE_DIR}/src/ ${qtwidgetsapp_BINARY_DIR}/src/)

find_package(Qt5 CONFIG REQUIRED COMPONENTS
   Widgets
)

add_subdirectory(src)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
