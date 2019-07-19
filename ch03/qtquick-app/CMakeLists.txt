cmake_minimum_required(VERSION 3.0)
project(qtquick-app)

include(FeatureSummary)

set(CMAKE_AUTORCC ON)

find_package(Qt5 CONFIG REQUIRED COMPONENTS
   Gui
   Qml
)

set(qtquick-app_SRC
   src/main.cpp
   src/main.qrc
)

add_executable(${PROJECT_NAME} ${qtquick-app_SRC})
target_link_libraries(${PROJECT_NAME} Qt5::Gui Qt5::Qml)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
