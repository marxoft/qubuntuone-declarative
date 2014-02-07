#include "plugin.h"
#include "declarativeaccount.h"
#include "declarativenodelistmodel.h"
#include "declarativestoragequota.h"
#include "declarativetoken.h"
#include "declarativeuser.h"
#include "filetransfer.h"
#include "node.h"
#include <qdeclarative.h>

namespace QtUbuntuOne {

void Plugin::registerTypes(const char *uri) {
    Q_ASSERT(uri == QLatin1String("com.marxoft.qubuntuone"));

    qRegisterMetaType<Node*>("Node*");
    qRegisterMetaType< QList<Node*> >("QList<Node*>");
    qRegisterMetaType<Node::NodeType>("Node::NodeType");
    qRegisterMetaType<Node::Error>("Node::Error");
    qRegisterMetaType<FileTransfer::Status>("FileTransfer::Status");
    qRegisterMetaType<FileTransfer::TransferType>("FileTransfer::TransferType");
    qRegisterMetaType<DeclarativeAccount::Error>("DeclarativeAccount::Error");
    qRegisterMetaType<DeclarativeNodeListModel::Status>("DeclarativeNodeListModel::Status");
    qRegisterMetaType<DeclarativeStorageQuota::Error>("DeclarativeStorageQuota::Error");
    qRegisterMetaType<DeclarativeToken::Error>("DeclarativeToken::Error");
    qRegisterMetaType<DeclarativeUser::Error>("DeclarativeUser::Error");

    qmlRegisterType<DeclarativeAccount>(uri, 1, 0, "QUbuntuOneAccount");
    qmlRegisterType<DeclarativeNodeListModel>(uri, 1, 0, "QUbuntuOneNodeListModel");
    qmlRegisterType<DeclarativeStorageQuota>(uri, 1, 0, "QUbuntuOneStorageQuota");
    qmlRegisterType<DeclarativeToken>(uri, 1, 0, "QUbuntuOneToken");
    qmlRegisterType<DeclarativeUser>(uri, 1, 0, "QUbuntuOneUser");
    qmlRegisterType<FileTransfer>(uri, 1, 0, "QUbuntuOneFileTransfer");
    qmlRegisterType<Node>(uri, 1, 0, "QUbuntuOneNode");
}

}

Q_EXPORT_PLUGIN2(qubuntuoneplugin, QtUbuntuOne::Plugin)
