set(qtwidgetsapp_SRC
   main.cpp
   main.qrc
   core.cpp
   plugincontroller.cpp
   uicontroller.cpp
)

add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE
   ${qtwidgetsapp_SRC}
)

target_link_libraries(${PROJECT_NAME}
   Qt5::Widgets
   QtWidgetsApp::Interfaces
)
