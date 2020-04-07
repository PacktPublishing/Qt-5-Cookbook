set(exampleplugin2_SRC
   exampleplugin2.cpp
)

add_library(exampleplugin2 MODULE ${exampleplugin2_SRC})

target_link_libraries(exampleplugin2
   Qt5::Widgets
   QtWidgetsApp::Interfaces
)
