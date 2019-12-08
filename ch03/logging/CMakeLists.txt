cmake_minimum_required(VERSION 3.0)
project(logging)

include(FeatureSummary)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 CONFIG REQUIRED COMPONENTS
   Core
)

set(logging_SRC
   src/main.cpp
   src/mycoordinate.cpp
)

add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE ${logging_SRC})
target_link_libraries(${PROJECT_NAME}
   Qt5::Core
)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
