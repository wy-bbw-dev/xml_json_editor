cmake_minimum_required(VERSION 3.25)
project(xml_json_editor)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Quick Widgets Xml)

qt_standard_project_setup()

qt_add_executable(xml_json_editor)
target_sources(xml_json_editor PRIVATE 
    main.cpp
    src/controller/FileController.cpp
    src/model/XmlModel.cpp
)

# moc needs header files
target_sources(xml_json_editor PRIVATE
    include/controller/FileController.h
    include/model/XmlModel.h
)


include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

target_link_libraries(xml_json_editor PRIVATE 
    Qt6::Widgets
    Qt6::Gui 
    Qt6::Quick 
    Qt6::Xml
    CONAN_PKG::spdlog
)

set_target_properties(xml_json_editor PROPERTIES
        CXX_STANDARD 23
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
)

target_include_directories(xml_json_editor PUBLIC 
    ${PROJECT_SOURCE_DIR}/include)


qt_add_qml_module(xml_json_editor
        URI xmljsoneditor
        VERSION 1.0
        QML_FILES
            ui/mainwindow/MainWindow.qml
            ui/mainwindow/MainMenu.qml
            ui/mainwindow/MainToolbar.qml
)
