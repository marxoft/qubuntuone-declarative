import QtQuick 1.0
import com.marxoft.qubuntuone 1.0

Rectangle {
    id: root

    width: 400
    height: 600

    QUbuntuOneToken {
        id: token
    }

    QUbuntuOneAccount {
        id: account

        onReady: {
            resultEdit.text = "";

            switch (error) {
            case QUbuntuOneAccount.NoError:
                resultEdit.text += qsTr("Id: ") + id + "\n";
                resultEdit.text += qsTr("Username: ") + username + "\n";
                resultEdit.text += qsTr("Nickname: ") + nickname + "\n";
                resultEdit.text += qsTr("First name: ") + firstName + "\n";
                resultEdit.text += qsTr("Last name: ") + lastName + "\n";
                resultEdit.text += qsTr("Email address: ") + email + "\n";
                resultEdit.text += qsTr("Open ID: ") + openId + "\n";
                resultEdit.text += qsTr("Total storage: ") + totalStorage + "\n";
                resultEdit.text += qsTr("Current plan: ") + currentPlan + "\n";
                resultEdit.text += qsTr("Features: ") + features.join(", ");
                return;
            default:
                resultEdit.text += qsTr("Error: ") + errorString;
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
            text: qsTr("Get account")
            onClicked: account.load()
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
