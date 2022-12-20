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
        onFileContent: (content) => xmlModel.receiveText(content)
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
        id: saveAs
        text: qsTr("Save as")
    }
    Action {
        id: exit   
        text: qsTr("Exit")
        onTriggered: Qt.quit()
    }

    RowLayout {
        ToolButton { action: openFile }
        ToolButton { action: save }
        ToolButton { action: saveAs }
        ToolButton { action: exit }
    }
}
