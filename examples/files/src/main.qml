import QtQuick 1.0
import com.marxoft.qubuntuone 1.0

Rectangle {
    id: root

    width: 400
    height: 600

    QUbuntuOneToken {
        id: token
    }

    Grid {
        id: grid

        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
            margins: 10
        }
        columns: 2
        spacing: 10

        Text {
            width: 125
            height: 30
            text: qsTr("Consumer key:")
        }

        TextInput {
            width: 245
            height: 30
            selectByMouse: true
            onTextChanged: token.consumerKey = text
        }

        Text {
            width: 125
            height: 30
            text: qsTr("Consumer secret:")
        }

        TextInput {
            width: 245
            height: 30
            selectByMouse: true
            onTextChanged: token.consumerSecret = text
        }

        Text {
            width: 125
            height: 30
            text: qsTr("Token key:")
        }

        TextInput {
            width: 245
            height: 30
            selectByMouse: true
            onTextChanged: token.tokenKey = text
        }

        Text {
            width: 125
            height: 30
            text: qsTr("Token secret:")
        }

        TextInput {
            width: 245
            height: 30
            selectByMouse: true
            onTextChanged: token.tokenSecret = text
        }

        Button {
            text: qsTr("Load model")
            onClicked: nodeModel.reload()
        }
    }

    ListView {
        id: view

        anchors {
            left: parent.left
            right: parent.right
            top: grid.bottom
            topMargin: 10
            bottom: row.top
            bottomMargin: 10
        }
        clip: true
        model: QUbuntuOneNodeListModel {
            id: nodeModel
        }

        delegate: Rectangle {
            width: view.width
            height: 40

            color: "transparent"
            border.width: 1
            border.color: "#000000"

            Column {
                anchors {
                    left: parent.left
                    leftMargin: 10
                    right: parent.right
                    rightMargin: 10
                    verticalCenter: parent.verticalCenter
                }

                Text {
                    width: parent.width
                    color: "#000000"
                    elide: Text.ElideRight
                    text: name
                }

                Text {
                    width: parent.width
                    color: "#4d4d4d"
                    elide: Text.ElideRight
                    text: Qt.formatDateTime(whenCreated)
                }
            }



            MouseArea {
                anchors.fill: parent
                onClicked: nodeModel.cd(index)
            }
        }
    }

    Row {
        id: row

        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
            margins: 10
        }
        spacing: 10

        Button {
            width: 185
            text: qsTr("Home")
            onClicked: nodeModel.cdRoot()
        }

        Button {
            width: 185
            text: qsTr("Up")
            onClicked: nodeModel.cdUp()
        }
    }
}
