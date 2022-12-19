import QtQuick
import QtQuick.Controls

ApplicationWindow {
    id: mainwindow
    visible: true
    menuBar: MainMenu{}
    header: MainToolbar { }
    width: 640
    height: 480
    //menuBar: MenuBar {
    //    Menu {
    //        title: "File"
    //        MenuItem { text: "open"}
    //    }
    //}
}
