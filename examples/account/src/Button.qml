import QtQuick 1.0

Rectangle {
    id: root

    property string text

    signal clicked

    width: 100
    height: 30
    color: mouseArea.pressed ? "#4d4d4d" : "transparent"
    border.color: "black"
    border.width: 1
    opacity: enabled ? 1 : 0.5

    Text {
        anchors.centerIn: parent
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        text: root.text
    }

    MouseArea {
        id: mouseArea

        anchors.fill: parent
        onClicked: root.clicked()
    }
}
