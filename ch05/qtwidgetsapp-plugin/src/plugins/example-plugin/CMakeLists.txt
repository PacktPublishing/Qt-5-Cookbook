set(exampleplugin_SRC
   exampleplugin.cpp
)

add_library(exampleplugin MODULE ${exampleplugin_SRC})

target_link_libraries(exampleplugin
   Qt5::Widgets
   QtWidgetsApp::Interfaces
)
