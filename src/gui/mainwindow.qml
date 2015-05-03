import QtQuick 2.4
import QtQuick.Window 2.0

Window
{
    id: mainwindow
    width: 600
    height: 800
    visible: true

    DropArea {
        id: schemaDrop
        anchors.fill: parent

        states: [
                State {
                    name: "onDrop"
                    PropertyChanges { target: mainwindow; color: "gray"; }
                },
                State {
                    name: "noDrop"
                    PropertyChanges { target: mainwindow; color: "white"; }
                }
            ]

        onEntered: {
            schemaDrop.state = "onDrop"
            drag.accept(Qt.MoveAction)
        }
        onDropped: {
            schemaDrop.state = "noDrop"
        }
        onExited: {
            schemaDrop.state = "noDrop"
        }
    }

}

