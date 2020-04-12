set(qtwidgetsappinterfaces_SRC
   icore.cpp
   iplugincontroller.cpp
   iuicontroller.cpp
)

add_library(qtwidgetsappinterfaces SHARED
            ${qtwidgetsappinterfaces_SRC})
add_library(QtWidgetsApp::Interfaces ALIAS qtwidgetsappinterfaces)

target_link_libraries(qtwidgetsappinterfaces
   Qt5::Core
)

generate_export_header(qtwidgetsappinterfaces EXPORT_FILE_NAME
                       qtwidgetsappinterfacesexport.h)

install(TARGETS qtwidgetsappinterfaces
        DESTINATION ${CMAKE_BINARY_DIR}/src/app/)
