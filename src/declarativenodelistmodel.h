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

/**
 * \file declarativenodelistmodel.h
 */

#ifndef DECLARATIVENODELISTMODEL_H
#define DECLARATIVENODELISTMODEL_H

#include "nodelist.h"
#include "reply.h"
#include <QAbstractListModel>

namespace QtUbuntuOne {

class DeclarativeNodeListModelPrivate;

/**
 * \class DeclarativeNodeListModel
 * \brief A data model for Ubuntu One nodes.
 *
 * DeclarativeNodeListModel provides a data model for accessing and
 * manipulating Ubuntu One nodes.
 *
 * DeclarativeNodeListModel provides access to its data via the
 * following role names:
 *
 * nodeType
 * path
 * resourcePath
 * contentPath
 * parentPath
 * volumePath
 * nodePath
 * name
 * suffix
 * key
 * whenCreated
 * lastModified
 * generation
 * generationCreated
 * hash
 * size
 * isPublic
 * publicUrl
 * hasChildren
 * isRoot
 */
class Q_DECL_EXPORT DeclarativeNodeListModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(Node* activeNode
               READ activeNode
               NOTIFY activeNodeChanged)
    Q_PROPERTY(int count
               READ rowCount
               NOTIFY countChanged)
    Q_PROPERTY(bool canPaste
               READ canPaste
               NOTIFY canPasteChanged)
    Q_PROPERTY(Status status
               READ status
               NOTIFY statusChanged)
    Q_PROPERTY(QString errorString
               READ errorString
               NOTIFY statusChanged)

    Q_ENUMS(Status)

public:
    /**
     * \enum Status
     */
    enum Status {
        Idle = 0,
        Loading,
        Ready,
        Error
    };

    explicit DeclarativeNodeListModel(QObject *parent = 0);
    ~DeclarativeNodeListModel();

#if QT_VERSION >= 0x050000
    /**
     * Re-implemented from QAbstractListModel
     */
    QHash<int, QByteArray> roleNames() const;
#endif
    /**
     * Re-implemented from QAbstractListModel
     */
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    
    /**
     * Re-implemented from QAbstractListModel
     */
    QVariant data(const QModelIndex &index, int role) const;

    /**
     * Provides access to the QAbstractListModel::data method using the
     * row number and the role name.
     */
    Q_INVOKABLE QVariant data(int row, const QByteArray &role) const;

    /**
     * Returns the Node* instance at the specified QModelIndex
     *
     * \param QModelIndex
     *
     * \return Node*
     */
    Node* get(const QModelIndex &index) const;

    /**
     * Returns the Node* instance at the specified row
     *
     * \param int
     *
     * \return Node*
     */
    Q_INVOKABLE Node* get(int row) const;

    Node* activeNode() const;

    /**
     * Returns whether a Node has been cut/copied, and can be pasted
     * to the current location.
     *
     * \return bool
     */
    bool canPaste() const;

    /**
     * Returns the status of the model.
     *
     * \return Status
     */
    Status status() const;

    /**
     * Returns the description of the last error.
     */
    QString errorString() const;

    /**
     * Reloads the child nodes of the active Node.
     */
    Q_INVOKABLE void reload();

    /**
     * Clears the child nodes the active Node.
     */
    Q_INVOKABLE void clear();

    /**
     * Sets the active Node to the Node at the specified row.
     *
     * \param int
     */
    Q_INVOKABLE void cd(int row);

    /**
     * Sets the active Node to the Node with the specified resource path.
     *
     * \param QString
     */
    Q_INVOKABLE void cd(const QString &resourcePath);

    /**
     * Sets the active Node to the parent of the current active Node.
     */
    Q_INVOKABLE void cdUp();

    /**
     * Sets the parent Node to the root Node.
     */
    Q_INVOKABLE void cdRoot();

    /**
     * Creates a new directory (or volume) under the active Node.
     *
     * \param QString
     */
    Q_INVOKABLE void makeDirectory(const QString &name);

    /**
     * Renames the Node at the specified row (files/directories only) to
     * the specified name.
     *
     * \param int
     * \param QString
     */
    Q_INVOKABLE void renameNode(int row, const QString &name);

    /**
     * Selects the Node at the specified row to be cut, ready for
     * pasting to a different location.
     *
     * \param int
     */
    Q_INVOKABLE void cutNode(int row);

    /**
     * Pastes the Node previously cut to the current location.
     */
    Q_INVOKABLE void pasteNode();

    /**
     * Deletes the Node at the specified row, along with its child nodes.
     *
     * \param int
     */
    Q_INVOKABLE void deleteNode(int row);

    /**
     * Sets whether the file Node at the specified row should be public.
     *
     * \param int
     * \param bool
     */
    Q_INVOKABLE void setFilePublic(int row, bool isPublic);

signals:
    /**
     * Emitted when the active Node changes.
     *
     * \param Node*
     */
    void activeNodeChanged(Node *node);

    /**
     * Emitted when the child Node count of the active Node changes.
     *
     * \param int
     */
    void countChanged(int count);

    /**
     * Emitted when the status of the model changes.
     *
     * \param Status
     */
    void statusChanged(DeclarativeNodeListModel::Status status);

    /**
     * Emitted when the model can/cannot paste a Node.
     *
     * \param bool
     */
    void canPasteChanged(bool canPaste);

    /**
     * Emitted when an error occurs, usually in response to an error
     * accessing the Ubuntu One API.
     *
     * \param QString
     */
    void error(const QString &errorString);

private:
    QScopedPointer<DeclarativeNodeListModelPrivate> d_ptr;

    Q_DECLARE_PRIVATE(DeclarativeNodeListModel)

    Q_PRIVATE_SLOT(d_func(), void _q_addNodes(NodeList *nodes))
    Q_PRIVATE_SLOT(d_func(), void _q_onNodeCreated(Node *node))
    Q_PRIVATE_SLOT(d_func(), void _q_onNodeDeleted(Reply *reply))
    Q_PRIVATE_SLOT(d_func(), void _q_onNodeDataChanged(Node *node))
};

}

Q_DECLARE_METATYPE(QtUbuntuOne::DeclarativeNodeListModel::Status)

#endif // DECLARATIVENODELISTMODEL_H
