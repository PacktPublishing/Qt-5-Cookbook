set(qtquickapp_SRC
   main.cpp
   main.qrc
   core.cpp
   plugincontroller.cpp
)

add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE
   ${qtquickapp_SRC}
)

target_link_libraries(${PROJECT_NAME}
   Qt5::Core
   Qt5::Gui
   Qt5::Qml
)
