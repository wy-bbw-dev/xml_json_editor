import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import xmljsoneditor

ApplicationWindow {
    id: mainwindow
    visible: true
    menuBar: MainMenu{}
    header: MainToolbar { }
    width: 1000
    height: 1000

    XmlModel {
        id: xmlModel
    }

    RowLayout{ 
        TreeView {}
    }
}
