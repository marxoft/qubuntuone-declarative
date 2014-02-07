import QtQuick 1.0
import com.marxoft.qubuntuone 1.0

Rectangle {
    id: root

    width: 400
    height: 600

    QUbuntuOneToken {
        id: token

        onReady: {
            resultEdit.text = "";

            switch (error) {
            case QUbuntuOneToken.NoError:
                resultEdit.text += qsTr("Token name: ") + tokenName + "\n";
                resultEdit.text += qsTr("Consumer key: ") + consumerKey + "\n";
                resultEdit.text += qsTr("Consumer secret: ") + consumerSecret + "\n";
                resultEdit.text += qsTr("Token key: ") + tokenKey + "\n";
                resultEdit.text += qsTr("Token secret: ") + tokenSecret;
                return;
            default:
                resultEdit.text += qsTr("Error : ") + errorString;
                return;
            }
        }
    }

    Flow {
        id: flow

        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
            margins: 10
        }
        spacing: 10

        Text {
            width: 125
            height: 30
            text: qsTr("Application name:")
        }

        TextInput {
            id: applicationNameEdit

            width: 245
            height: 30
            selectByMouse: true
        }

        Text {
            width: 125
            height: 30
            text: qsTr("Email:")
        }

        TextInput {
            id: emailEdit

            width: 245
            height: 30
            selectByMouse: true
        }

        Text {
            width: 125
            height: 30
            text: qsTr("Password:")
        }

        TextInput {
            id: passwordEdit

            width: 245
            height: 30
            selectByMouse: true
            echoMode: TextInput.Password
        }

        Text {
            width: 125
            height: 30
            text: qsTr("One time password:")
        }

        TextInput {
            id: otpEdit

            width: 245
            height: 30
            selectByMouse: true
            echoMode: TextInput.Password
        }

        Button {
            id: actionButton

            text: qsTr("Authenticate")
            onClicked: token.authenticate(emailEdit.text, passwordEdit.text, otpEdit.text, applicationNameEdit.text)
        }

        Text {
            width: parent.width
            text: qsTr("Result:")
        }

        TextEdit {
            id: resultEdit

            width: parent.width
            height: 200
            readOnly: true
            selectByMouse: true
        }
    }
}
