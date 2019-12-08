cmake_minimum_required(VERSION 3.0)
project(i18n-l10n)

set_directory_properties(PROPERTIES CLEAN_NO_CUSTOM 1)

include(FeatureSummary)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 CONFIG REQUIRED COMPONENTS
   Widgets
   LinguistTools
)

set(i18n-l10n_SRC
   src/main.cpp
   src/main.qrc
   src/mainwindow.cpp
)

add_definitions(-DQT_NO_CAST_FROM_ASCII)

qt5_create_translation(i18n-l10n_QM ${i18n-l10n_SRC}
   l10n/${PROJECT_NAME}_en_US.ts
   l10n/${PROJECT_NAME}_pt_BR.ts
)
configure_file(src/l10n.qrc ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
qt5_add_resources(i18n-l10n_SRC ${CMAKE_CURRENT_BINARY_DIR}/l10n.qrc)

add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE
   ${i18n-l10n_SRC} ${i18n-l10n_QM}
)
target_link_libraries(${PROJECT_NAME}
   Qt5::Widgets
)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
