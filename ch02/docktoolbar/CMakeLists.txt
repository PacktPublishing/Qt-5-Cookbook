cmake_minimum_required(VERSION 3.0)
project(docktoolbar)

include(FeatureSummary)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 CONFIG REQUIRED COMPONENTS
   Widgets
   WebEngineWidgets
)

set(docktoolbar_SRC
   src/main.cpp
   src/main.qrc
   src/mainwindow.cpp
   src/orientabletoolbutton.cpp
   src/docktoolbar.cpp
)

add_executable(${PROJECT_NAME} ${docktoolbar_SRC})
target_link_libraries(${PROJECT_NAME}
   Qt5::Widgets
   Qt5::WebEngineWidgets
)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
