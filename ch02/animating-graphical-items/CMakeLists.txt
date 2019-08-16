cmake_minimum_required(VERSION 3.0)
project(animating-graphical-items)

include(FeatureSummary)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 CONFIG REQUIRED COMPONENTS
   Widgets
)

set(animating-graphical-items_SRC
   src/main.cpp
   src/main.qrc
   src/mainwindow.cpp
)

add_executable(${PROJECT_NAME} ${animating-graphical-items_SRC})
target_link_libraries(${PROJECT_NAME}
   Qt5::Widgets
)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
