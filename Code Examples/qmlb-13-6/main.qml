import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.0
import QtQuick.Controls 2.5
//import QtQuick.Dialogs 1.2
import Qt.labs.platform 1.1

import com.company.backend 1.0


ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Backend {
        id: backend
        onPathChanged: console.log("Path:", path)
        onDataChanged: console.log("Path:", path)
    }

    FileDialog {
        id: openDialog
        title: "Please choose a file"
        //folder: shortcuts.home
        fileMode: FileDialog.OpenFile
        //selectMultiple: false
        //selectExisting: true

        onAccepted: {
            backend.path = openDialog.fileUrl
            editor.text = backend.data
        }
    }

    FileDialog {
        id: saveDialog
        title: "Please choose a file"
        //folder: shortcuts.home
        fileMode: FileDialog.SaveFile
        //selectMultiple: false
        //selectExisting: false

        onAccepted: {
            backend.path = saveDialog.fileUrl
            backend.data = editor.text
        }
    }

    Action {
        id: actionNew
        text: qsTr("New")
        icon.color: "transparent"
        icon.source: "qrc:/flat/outlines/oNew.png"
        onTriggered: editor.clear()
    }

    Action {
        id: actionOpen
        text: qsTr("Open")
        icon.color: "transparent"
        icon.source: "qrc:/flat/outlines/oOpen.png"
        onTriggered: openDialog.open()
    }

    Action {
        id: actionSave
        text: qsTr("Open")
        icon.color: "transparent"
        icon.source: "qrc:/flat/outlines/oSave.png"
        onTriggered: saveDialog.open()
    }

    Action {
        id: actionCopy
        text: qsTr("Copy")
        icon.color: "transparent"
        icon.source: "qrc:/flat/outlines/oCopy.png"
        onTriggered: editor.copy()
    }

    Action {
        id: actionCut
        text: qsTr("Cut")
        icon.color: "transparent"
        icon.source: "qrc:/flat/outlines/oCut.png"
        onTriggered: editor.cut()
    }

    Action {
        id: actionPaste
        text: qsTr("Paste")
        icon.color: "transparent"
        icon.source: "qrc:/flat/outlines/oPaste.png"
        onTriggered: editor.paste()
    }

/*
    menuBar: MenuBar {
        id: menuBar
        Menu {
            id: fileMenu
            title: qsTr("File")
        }
    }

    menuBar: MenuBar {
        Menu {
            id: menuFile
            title: qsTr("File")
            MenuItem {
                text: actionNew.text
                onTriggered: actionNew.trigger
            }

            menuItem { action: actionNew }
            MenuItem { action: actionOpen }
            MenuItem { action: actionSave }
        }

        Menu {
            id: menuEdit
            title: qsTr("Edit")
            MenuItem { action: actionCopy }
            MenuItem { action: actionCut }
            MenuItem { action: actionPaste }
        }
    }
   */

    header: ToolBar {
        Row {
            ToolButton {display: AbstractButton.IconOnly; action: actionNew}
            ToolButton {display: AbstractButton.IconOnly; action: actionOpen}
            ToolButton {display: AbstractButton.IconOnly; action: actionSave}
            ToolButton {display: AbstractButton.IconOnly; action: actionCopy}
            ToolButton {display: AbstractButton.IconOnly; action: actionCut}
            ToolButton {display: AbstractButton.IconOnly; action: actionPaste}
        }
    }

    ScrollView {
        anchors.fill: parent
        TextArea {
            id: editor
            focus: true
            text: "Hello World"
            selectByMouse:  true
            persistentSelection: true //copy and paste need this!
        }
    }

}
