cmake_minimum_required(VERSION 3.25)
project(xml_json_editor)
find_package(Qt6 REQUIRED COMPONENTS Gui Quick)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 23)

qt_add_executable(xml_json_editor)
target_sources(xml_json_editor PRIVATE main.cpp)

target_link_libraries(xml_json_editor PRIVATE Qt6::Gui Qt6::Quick)

set_target_properties(xml_json_editor PROPERTIES
        CXX_STANDARD 23
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF)

qt_add_qml_module(xml_json_editor
        URI xml_json
        VERSION 1.0
        QML_FILES
            ui/mainwindow/MainWindow.qml
            ui/mainwindow/MainMenu.qml
)




