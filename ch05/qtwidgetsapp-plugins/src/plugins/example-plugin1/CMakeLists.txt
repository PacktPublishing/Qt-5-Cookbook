set(exampleplugin1_SRC
   exampleplugin1.cpp
)

add_library(exampleplugin1 MODULE ${exampleplugin1_SRC})

target_link_libraries(exampleplugin1
   Qt5::Widgets
   QtWidgetsApp::Interfaces
)

install(TARGETS exampleplugin1
        DESTINATION ${CMAKE_BINARY_DIR}/src/app/plugins/)
