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

#ifndef DECLARATIVENODELISTMODEL_P_H
#define DECLARATIVENODELISTMODEL_P_H

#include "declarativenodelistmodel.h"

namespace QtUbuntuOne {

class DeclarativeNodeListModelPrivate
{

public:
    enum Role {
        NodeTypeRole = Qt::UserRole + 1,
        PathRole,
        ResourcePathRole,
        ContentPathRole,
        ParentPathRole,
        VolumePathRole,
        NodePathRole,
        NameRole,
        SuffixRole,
        KeyRole,
        WhenCreatedRole,
        LastModifiedRole,
        GenerationRole,
        GenerationCreatedRole,
        HashRole,
        SizeRole,
        IsPublicRole,
        PublicUrlRole,
        HasChildrenRole,
        IsRootRole
    };

    DeclarativeNodeListModelPrivate(DeclarativeNodeListModel *parent);
    virtual ~DeclarativeNodeListModelPrivate();

#if QT_VERSION >= 0x050000
    QHash<int, QByteArray> roleNames() const;
#endif
    int rowCount() const;

    QVariant data(const QModelIndex &index, int role) const;
    QVariant data(int row, const QByteArray &role) const;

    Node* get(const QModelIndex &index) const;
    Node* get(int row) const;
    Node* get(const QString &path) const;

    Node* activeNode() const;

    bool canPaste() const;

    DeclarativeNodeListModel::Status status() const;

    QString errorString() const;

    void reload();
    void clear();

    void cd(int row);
    void cd(const QString &resourcePath);
    void cdUp();
    void cdRoot();

    void makeDirectory(const QString &name);

    void renameNode(int row, const QString &name);
    void cutNode(int row);
    void pasteNode();
    void deleteNode(int row);

    void setFilePublic(int row, bool isPublic);


private:
    void setActiveNode(Node *node);

    void setCanPaste(bool paste);

    void setStatus(DeclarativeNodeListModel::Status status);

    void setErrorString(const QString &errorString);

    void insertNode(int pos, Node *node, Node *parentNode);
    void insertNodeAlphabetically(Node *node, Node *parentNode);
    void appendNode(Node *node, Node *parentNode);
    void removeNode(int pos, Node *parentNode);
    void removeNodes(int pos, int count, Node *parentNode);

    void _q_addNodes(NodeList *nodes);

    void _q_onNodeCreated(Node *node);
    void _q_onNodeDeleted(Reply *reply);
    void _q_onNodeDataChanged(Node *node);

    DeclarativeNodeListModel *q_ptr;

    Node *m_rootNode;
    Node *m_activeNode;
    Node *m_actionNode;

    bool m_canPaste;

    DeclarativeNodeListModel::Status m_status;

    QString m_errorString;

    QHash<int, QByteArray> m_roleNames;

    Q_DECLARE_PUBLIC(DeclarativeNodeListModel)
};

}

#endif // DECLARATIVENODELISTMODEL_P_H
