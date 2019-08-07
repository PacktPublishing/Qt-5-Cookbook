cmake_minimum_required(VERSION 3.0)
project(simple-qtquick)

include(FeatureSummary)

set(CMAKE_AUTORCC ON)

find_package(Qt5 CONFIG REQUIRED COMPONENTS
   Gui
   Qml
)

set(simple-qtquick_SRC
   src/main.cpp
   src/main.qrc
)

add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE ${simple-qtquick_SRC})
target_link_libraries(${PROJECT_NAME} Qt5::Gui Qt5::Qml)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
