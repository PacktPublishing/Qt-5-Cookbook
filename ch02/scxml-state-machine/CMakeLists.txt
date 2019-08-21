cmake_minimum_required(VERSION 3.0)
project(scxml-state-machine)

include(FeatureSummary)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 CONFIG REQUIRED COMPONENTS
   Widgets
   Scxml
)

set(scxml-state-machine_SRC
   src/main.cpp
   src/main.qrc
   src/mainwindow.cpp
)

cmake_policy(SET CMP0071 NEW)
set_property(SOURCE statemachine.h PROPERTY SKIP_AUTOMOC ON)
qt5_add_statecharts(scxml-state-machine_SRC
   src/statemachine.scxml
   OPTIONS --statemethods --output statemachine --classname StateMachine
)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE ${scxml-state-machine_SRC})
target_link_libraries(${PROJECT_NAME}
   Qt5::Widgets
   Qt5::Scxml
)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
