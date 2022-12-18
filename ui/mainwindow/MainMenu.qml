import QtQuick.Controls

MenuBar {
    id: mainMenu
    Menu {
        title: "File"
        MenuItem {
            text: "Open"
        }
        MenuItem {
            text: "Save"
        }
        MenuItem {
            text: "Save as"
        }
        MenuItem {
            text: "Close"
        }
    }
}
