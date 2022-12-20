import QtCore
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs
import xmljsoneditor

ToolBar {
    FileDialog {
        id: fileDialog
        currentFolder: fileController.folder
        onAccepted: {
            fileController.file = selectedFile
        }
    }

    FileController {
        id: fileController
    }
    Action {
        id: openFile
        text: qsTr("Open file")
        onTriggered: {
            fileDialog.open()
        }
    }
    Action {
        id: save
        text: qsTr("Save")
    }
    Action {
        id: exit   
        text: qsTr("Exit")
        onTriggered: Qt.quit()
    }

    RowLayout {
        ToolButton { action: openFile }
        ToolButton { action: save }
        ToolButton { action: exit }
    }
}
