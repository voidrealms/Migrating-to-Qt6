import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3
//import QtQuick.Dialogs 1.3
import Qt.labs.platform 1.0


import com.company.animal 1.0

Window {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Column {
        id: column
        width: 344
        height: 284
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        Grid {
            id: grid
            width: 284
            height: 226
            spacing: 15
            rows: 6
            columns: 2

            Label {
                text: qsTr("Name")
            }

            TextField {
                id: txtName
                selectByMouse: true
                text: qsTr("Text Field")
            }

            Label {
                text: qsTr("Species")
            }

            TextField {
                id: txtSpecies
                selectByMouse: true
                text: qsTr("Text Field")
            }

            Label {
                text: qsTr("Age")
            }

            SpinBox {
                id: sbAge
            }

            Label {
                text: qsTr("Fed")
            }

            TextField {
                id: txtFed
                selectByMouse: true
                text: qsTr("Text Field")
            }

        }

        Row {
            id: row
            width: 352
            height: 50
            spacing: 15

            Button {
                id: btnSave
                text: qsTr("Save")
                onClicked: {

                    animal.name = txtName.text
                    animal.species = txtSpecies.text
                    animal.age = sbAge.value
                    var d = new Date(txtFed.text)
                    animal.fed = d

                    saveDialog.open()

                }
            }

            Button {
                id: btnClear
                text: qsTr("Clear")
                onClicked: {
                    animal.clear()
                    updateGUI()
                }
            }

            Button {
                id: btnLoad
                text: qsTr("Load")
                onClicked:  {
                    animal.clear()
                    openDialog.open()
                }
            }
        }
    }

    FileDialog {
        id: saveDialog
        title: "Please choose a file"
        //selectMultiple: false
        //selectExisting : false
        fileMode: FileDialog.SaveFile

        onAccepted: {
            //var path = saveDialog.fileUrl.toString().replace("file://","")
            var path = saveDialog.file.toString().replace("file://","")
            console.log("You chose: " + path)
            animal.toFile(path)
        }
        onRejected: {
            console.log("Canceled")
        }
    }

    FileDialog {
        id: openDialog
        title: "Please choose a file"
        //selectMultiple: false
        //selectExisting : true
        fileMode: FileDialog.OpenFile

        onAccepted: {

           // var path = openDialog.fileUrl.toString().replace("file://","")
            var path = openDialog.file.toString().replace("file://","")
            console.log("You chose: " + path)
            animal.fromFile(path)
        }
        onRejected: {
            console.log("Canceled")
        }
    }

    function updateGUI()
    {
        txtName.text = animal.name
        txtSpecies.text = animal.species
        sbAge.value = animal.age

        var d = new Date(animal.fed)
        console.log("Date: " + d)
        txtFed.text = d
    }

    Animal {
        id: animal
        onFinished: {
          updateGUI();
        }
        onError: {
            console.log(message)
        }

        Component.onCompleted: {
            updateGUI();
        }

    }

}
