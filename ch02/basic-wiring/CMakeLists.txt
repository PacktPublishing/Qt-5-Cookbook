cmake_minimum_required(VERSION 3.0)
project(basic-wiring)

include(FeatureSummary)

set(CMAKE_AUTOMOC ON)

find_package(Qt5 CONFIG REQUIRED COMPONENTS
   Widgets
)

add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE
   src/mycounter.cpp
   src/main.cpp
)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
