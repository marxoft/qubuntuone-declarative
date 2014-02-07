/*
 * Copyright (C) 2014 Stuart Howarth <showarth@marxoft.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU Lesser General Public License,
 * version 3, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "declarativenodelistmodel_p.h"
#include "files.h"

namespace QtUbuntuOne {

DeclarativeNodeListModelPrivate::DeclarativeNodeListModelPrivate(DeclarativeNodeListModel *parent) :
    q_ptr(parent),
    m_rootNode(new Node(parent)),
    m_activeNode(m_rootNode),
    m_actionNode(0),
    m_canPaste(false),
    m_status(DeclarativeNodeListModel::Idle)
{
    Q_Q(DeclarativeNodeListModel);

    m_roleNames[NodeTypeRole] = "nodeType";
    m_roleNames[PathRole] = "path";
    m_roleNames[ResourcePathRole] = "resourcePath";
    m_roleNames[ContentPathRole] = "contentPath";
    m_roleNames[ParentPathRole] = "parentPath";
    m_roleNames[VolumePathRole] = "volumePath";
    m_roleNames[NodePathRole] = "nodePath";
    m_roleNames[NameRole] = "name";
    m_roleNames[SuffixRole] = "suffix";
    m_roleNames[KeyRole] = "key";
    m_roleNames[WhenCreatedRole] = "whenCreated";
    m_roleNames[LastModifiedRole] = "lastModified";
    m_roleNames[GenerationRole] = "generation";
    m_roleNames[GenerationCreatedRole] = "generationCreated";
    m_roleNames[HashRole] = "hash";
    m_roleNames[SizeRole] = "size";
    m_roleNames[IsPublicRole] = "isPublic";
    m_roleNames[PublicUrlRole] = "publicUrl";
    m_roleNames[HasChildrenRole] = "hasChildren";
    m_roleNames[IsRootRole] = "isRoot";
#if QT_VERSION < 0x050000
    q->setRoleNames(m_roleNames);
#endif
}

DeclarativeNodeListModelPrivate::~DeclarativeNodeListModelPrivate() {}

#if QT_VERSION >= 0x050000
QHash<int, QByteArray> DeclarativeNodeListModelPrivate::roleNames() const {
    return m_roleNames;
}
#endif

int DeclarativeNodeListModelPrivate::rowCount() const {
    return m_activeNode ? m_activeNode->childNodeCount() : m_rootNode->childNodeCount();
}

QVariant DeclarativeNodeListModelPrivate::data(const QModelIndex &index, int role) const {
    if (Node *node = this->get(index)) {
        switch (role) {
        case NodeTypeRole:
            return node->nodeType();
        case PathRole:
            return node->path();
        case ResourcePathRole:
            return node->resourcePath();
        case ContentPathRole:
            return node->contentPath();
        case ParentPathRole:
            return node->parentPath();
        case VolumePathRole:
            return node->volumePath();
        case NodePathRole:
            return node->nodePath();
        case NameRole:
            return node->name();
        case SuffixRole:
            return node->suffix();
        case KeyRole:
            return node->key();
        case WhenCreatedRole:
            return node->whenCreated();
        case LastModifiedRole:
            return node->lastModified();
        case GenerationRole:
            return node->generation();
        case GenerationCreatedRole:
            return node->generationCreated();
        case HashRole:
            return node->hash();
        case SizeRole:
            return node->size();
        case IsPublicRole:
            return node->isPublic();
        case PublicUrlRole:
            return node->publicUrl();
        case HasChildrenRole:
            return node->hasChildren();
        case IsRootRole:
            return node->isRoot();
        default:
            break;
        }
    }

    return QVariant();
}

QVariant DeclarativeNodeListModelPrivate::data(int row, const QByteArray &role) const {
    Q_Q(const DeclarativeNodeListModel);

    return this->data(q->index(row), m_roleNames.key(role));
}

Node* DeclarativeNodeListModelPrivate::get(const QModelIndex &index) const {
    return this->get(index.row());
}

Node* DeclarativeNodeListModelPrivate::get(int row) const {
    return m_activeNode ? m_activeNode->childNode(row) : m_rootNode->childNode(row);
}

Node* DeclarativeNodeListModelPrivate::get(const QString &path) const {
    if (!m_activeNode) {
        return 0;
    }

    foreach (Node *node, m_activeNode->childNodes()) {
        switch (node->nodeType()) {
        case Node::Volume:
            if (node->nodePath() == path) {
                return node;
            }

            break;
        default:
            if (node->resourcePath() == path) {
                return node;
            }

            break;
        }
    }

    return 0;
}

Node* DeclarativeNodeListModelPrivate::activeNode() const {
    return !m_activeNode ? m_rootNode : m_activeNode;
}

void DeclarativeNodeListModelPrivate::setActiveNode(Node *node) {
    Q_Q(DeclarativeNodeListModel);

    q->beginResetModel();
    m_activeNode = node;
    q->endResetModel();

    if (node->childNodeCount() == 0) {
        this->setStatus(DeclarativeNodeListModel::Loading);

        switch (node->nodeType()) {
        case Node::Volume:
            q->connect(Files::listDirectory(node->nodePath()), SIGNAL(ready(NodeList*)), q, SLOT(_q_addNodes(NodeList*)));
            break;
        default:
            q->connect(Files::listDirectory(node->resourcePath()), SIGNAL(ready(NodeList*)), q, SLOT(_q_addNodes(NodeList*)));
            break;
        }
    }

    emit q->activeNodeChanged(node);
    emit q->countChanged(this->rowCount());
}

bool DeclarativeNodeListModelPrivate::canPaste() const {
    return m_canPaste;
}

void DeclarativeNodeListModelPrivate::setCanPaste(bool paste) {
    Q_Q(DeclarativeNodeListModel);

    if (paste != this->canPaste()) {
        m_canPaste = paste;
        emit q->canPasteChanged(paste);
    }
}

DeclarativeNodeListModel::Status DeclarativeNodeListModelPrivate::status() const {
    return m_status;
}

void DeclarativeNodeListModelPrivate::setStatus(DeclarativeNodeListModel::Status status) {
    Q_Q(DeclarativeNodeListModel);

    if (status != this->status()) {
        m_status = status;
        emit q->statusChanged(status);
    }
}

QString DeclarativeNodeListModelPrivate::errorString() const {
    return m_errorString;
}

void DeclarativeNodeListModelPrivate::setErrorString(const QString &errorString) {
    m_errorString = errorString;
}

void DeclarativeNodeListModelPrivate::reload() {
    Q_Q(DeclarativeNodeListModel);

    this->clear();

    if (m_activeNode) {
        this->setStatus(DeclarativeNodeListModel::Loading);

        if (m_activeNode == m_rootNode) {
            q->connect(Files::getVolumes(), SIGNAL(ready(NodeList*)), q, SLOT(_q_addNodes(NodeList*)));
        }
        else {
            switch (m_activeNode->nodeType()) {
            case Node::Volume:
                q->connect(Files::listDirectory(m_activeNode->nodePath()), SIGNAL(ready(NodeList*)), q, SLOT(_q_addNodes(NodeList*)));
                return;
            default:
                q->connect(Files::listDirectory(m_activeNode->resourcePath()), SIGNAL(ready(NodeList*)), q, SLOT(_q_addNodes(NodeList*)));
                return;
            }
        }
    }
}

void DeclarativeNodeListModelPrivate::clear() {
    if (m_activeNode) {
        this->removeNodes(0, m_activeNode->childNodeCount(), m_activeNode);
    }
}

void DeclarativeNodeListModelPrivate::cd(int row) {
    switch (this->status()) {
    case DeclarativeNodeListModel::Loading:
        return;
    default:
        break;
    }

    if (Node *node = this->get(row)) {
        switch (node->nodeType()) {
        case Node::File:
            return;
        default:
            this->setActiveNode(node);
            return;
        }
    }
}

void DeclarativeNodeListModelPrivate::cd(const QString &resourcePath) {
    switch (this->status()) {
    case DeclarativeNodeListModel::Loading:
        return;
    default:
        break;
    }

    if (Node *node = this->get(resourcePath)) {
        switch (node->nodeType()) {
        case Node::File:
            return;
        default:
            this->setActiveNode(node);
            return;
        }
    }
}

void DeclarativeNodeListModelPrivate::cdUp() {
    switch (this->status()) {
    case DeclarativeNodeListModel::Loading:
        return;
    default:
        break;
    }

    if (m_activeNode->parentNode()) {
        this->setActiveNode(m_activeNode->parentNode());
    }
}

void DeclarativeNodeListModelPrivate::cdRoot() {
    switch (this->status()) {
    case DeclarativeNodeListModel::Loading:
        return;
    default:
        break;
    }

    if (m_activeNode != m_rootNode) {
        this->setActiveNode(m_rootNode);
    }
}

void DeclarativeNodeListModelPrivate::makeDirectory(const QString &name) {
    Q_Q(DeclarativeNodeListModel);

    this->setStatus(DeclarativeNodeListModel::Loading);

    if (m_activeNode == m_rootNode) {
        q->connect(Files::createVolume(name), SIGNAL(ready(Node*)), q, SLOT(_q_onNodeCreated(Node*)));
    }
    else {
        switch (m_activeNode->nodeType()) {
        case Node::Volume:
            q->connect(Files::makeDirectory(m_activeNode->nodePath() + '/' + name), SIGNAL(ready(Node*)), q, SLOT(_q_onNodeCreated(Node*)));
            return;
        default:
            q->connect(Files::makeDirectory(m_activeNode->resourcePath() + '/' + name), SIGNAL(ready(Node*)), q, SLOT(_q_onNodeCreated(Node*)));
            return;
        }
    }
}

void DeclarativeNodeListModelPrivate::renameNode(int row, const QString &name) {
    Q_Q(DeclarativeNodeListModel);

    if (Node *node = this->get(row)) {
        switch (node->nodeType()) {
        case Node::Volume:
            this->setErrorString(QObject::tr("Volumes cannot be renamed"));
            this->setStatus(DeclarativeNodeListModel::Error);
            return;
        default:
            this->setStatus(DeclarativeNodeListModel::Loading);
            this->setCanPaste(false);
            m_actionNode = node;
            q->connect(Files::moveNode(node->resourcePath(), node->path().section('/', 0, -2) + '/' + name), SIGNAL(ready(Node*)), q, SLOT(_q_onNodeDataChanged(Node*)));
            return;
        }
    }
}

void DeclarativeNodeListModelPrivate::cutNode(int row) {
    if (Node *node = this->get(row)) {
        switch (node->nodeType()) {
        case Node::Volume:
            this->setErrorString(QObject::tr("Volumes cannot be moved"));
            this->setStatus(DeclarativeNodeListModel::Error);
            return;
        default:
            this->setCanPaste(true);
            m_actionNode = node;
            return;
        }
    }
}

void DeclarativeNodeListModelPrivate::pasteNode() {
    Q_Q(DeclarativeNodeListModel);

    if (m_actionNode) {
        this->setStatus(DeclarativeNodeListModel::Loading);
        switch (m_activeNode->nodeType()) {
        case Node::Volume:
            q->connect(Files::moveNode(m_actionNode->resourcePath(), '/' + m_actionNode->name()),
                       SIGNAL(ready(Node*)), q, SLOT(_q_onNodeDataChanged(Node*)));
            return;
        default:
            q->connect(Files::moveNode(m_actionNode->resourcePath(), m_activeNode->path() + '/' + m_actionNode->name()),
                       SIGNAL(ready(Node*)), q, SLOT(_q_onNodeDataChanged(Node*)));
            return;
        }
    }
}

void DeclarativeNodeListModelPrivate::deleteNode(int row) {
    Q_Q(DeclarativeNodeListModel);

    if (Node *node = this->get(row)) {
        this->setStatus(DeclarativeNodeListModel::Loading);
        this->setCanPaste(false);
        m_actionNode = node;
        q->connect(Files::deleteNode(node->resourcePath()), SIGNAL(finished(Reply*)), q, SLOT(_q_onNodeDeleted(Reply*)));
    }
}

void DeclarativeNodeListModelPrivate::setFilePublic(int row, bool isPublic) {
    Q_Q(DeclarativeNodeListModel);

    if (Node *node = this->get(row)) {
        this->setStatus(DeclarativeNodeListModel::Loading);
        this->setCanPaste(false);
        m_actionNode = node;
        q->connect(Files::setFilePublic(node->resourcePath(), isPublic), SIGNAL(ready(Node*)), q, SLOT(_q_onNodeDataChanged(Node*)));
    }
}

void DeclarativeNodeListModelPrivate::appendNode(Node *node, Node *parentNode) {
    Q_Q(DeclarativeNodeListModel);

    int count = parentNode->childNodeCount();
    q->beginInsertRows(QModelIndex(), count, count);
    parentNode->addChildNode(node);
    node->setParent(parentNode);
    q->endInsertRows();

    emit q->countChanged(this->rowCount());
}

void DeclarativeNodeListModelPrivate::insertNode(int pos, Node *node, Node *parentNode) {
    Q_Q(DeclarativeNodeListModel);

    if ((pos >= 0) && (pos < parentNode->childNodeCount())) {
        q->beginInsertRows(QModelIndex(), pos, pos);
        parentNode->insertChildNode(pos, node);
        node->setParent(parentNode);
        q->endInsertRows();

        emit q->countChanged(this->rowCount());
    }
    else {
        this->appendNode(node, parentNode);
    }
}

void DeclarativeNodeListModelPrivate::insertNodeAlphabetically(Node *node, Node *parentNode) {
    int i = 0;

    switch (node->nodeType()) {
    case Node::File:
        foreach (Node *childNode, parentNode->childNodes()) {
            if ((childNode->nodeType() == Node::File) && (childNode->path().compare(node->path(), Qt::CaseInsensitive) > 0)) {
                break;
            }

            i++;
        }

        break;
    default:
        foreach (Node *childNode, parentNode->childNodes()) {
            if ((childNode->nodeType() == Node::File) || (childNode->path().compare(node->path(), Qt::CaseInsensitive) > 0)) {
                break;
            }

            i++;
        }

        break;
    }

    this->insertNode(i, node, parentNode);
}

void DeclarativeNodeListModelPrivate::removeNode(int pos, Node *parentNode) {
    Q_Q(DeclarativeNodeListModel);

    if ((pos >= 0) && (pos < parentNode->childNodeCount())) {
        q->beginRemoveRows(QModelIndex(), pos, pos);

        if (Node *childNode = parentNode->removeChildNode(pos)) {
            childNode->deleteLater();
        }

        q->endRemoveRows();

        emit q->countChanged(this->rowCount());
    }
}

void DeclarativeNodeListModelPrivate::removeNodes(int pos, int count, Node *parentNode) {
    Q_Q(DeclarativeNodeListModel);

    if ((pos >= 0) && ((pos + count) <= parentNode->childNodeCount())) {
        q->beginRemoveRows(QModelIndex(), pos, pos + count - 1);

        for (int i = pos; i < (pos + count); i++) {
            if (Node *childNode = parentNode->removeChildNode(pos)) {
                childNode->deleteLater();
            }
        }

        q->endRemoveRows();

        emit q->countChanged(this->rowCount());
    }
}

void DeclarativeNodeListModelPrivate::_q_addNodes(NodeList *nodes) {
    switch (nodes->error()) {
    case NodeList::NoError:
        foreach (Node *node, nodes->nodes()) {
            this->insertNodeAlphabetically(node, m_activeNode);
        }

        this->setStatus(DeclarativeNodeListModel::Ready);
        break;
    default:
        this->setErrorString(nodes->errorString());
        this->setStatus(DeclarativeNodeListModel::Error);
        break;
    }

    nodes->deleteLater();
}

void DeclarativeNodeListModelPrivate::_q_onNodeCreated(Node *node) {
    switch (node->error()) {
    case Node::NoError:
        this->insertNodeAlphabetically(node, m_activeNode);
        this->setStatus(DeclarativeNodeListModel::Ready);
        return;
    default:
        this->setErrorString(node->errorString());
        this->setStatus(DeclarativeNodeListModel::Error);
        break;
    }

    node->deleteLater();
}

void DeclarativeNodeListModelPrivate::_q_onNodeDeleted(Reply *reply) {
    switch (reply->error()) {
    case Reply::NoError:
        this->removeNode(m_actionNode->index(), m_actionNode->parentNode());
        this->setStatus(DeclarativeNodeListModel::Ready);
        break;
    default:
        this->setErrorString(reply->errorString());
        this->setStatus(DeclarativeNodeListModel::Error);
        break;
    }

    reply->deleteLater();
}

void DeclarativeNodeListModelPrivate::_q_onNodeDataChanged(Node *node) {
    switch (node->error()) {
    case Node::NoError:
        this->setCanPaste(false);
        this->removeNode(m_actionNode->index(), m_actionNode->parentNode());
        this->insertNodeAlphabetically(node, m_activeNode);
        this->setStatus(DeclarativeNodeListModel::Ready);
        return;
    default:
        this->setErrorString(node->errorString());
        this->setStatus(DeclarativeNodeListModel::Error);
        break;
    }

    node->deleteLater();
}

}
