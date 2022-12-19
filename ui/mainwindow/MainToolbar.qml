import QtQuick.Controls
import QtQuick.Layouts

ToolBar {
    Action {
        id: openFile
        text: qsTr("Open file")
    }
    Action {
        id: save
        text: qsTr("Save")
    }
    Action {
        id: exit   
        text: qsTr("Exit")
    }

    RowLayout {
        ToolButton { action: openFile }
        ToolButton { action: save }
        ToolButton { action: exit }
    }
}
