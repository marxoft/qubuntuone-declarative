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

#include "declarativenodelistmodel.h"
#include "declarativenodelistmodel_p.h"

namespace QtUbuntuOne {

DeclarativeNodeListModel::DeclarativeNodeListModel(QObject *parent) :
    QAbstractListModel(parent),
    d_ptr(new DeclarativeNodeListModelPrivate(this))
{
}

DeclarativeNodeListModel::~DeclarativeNodeListModel() {}

#if QT_VERSION >= 0x050000
/**
 * roleNames
 */
QHash<int, QByteArray> DeclarativeNodeListModel::roleNames() const {
    Q_D(const DeclarativeNodelistModel);

    return d->roleNames();
}
#endif

/**
 * rowCount
 */
int DeclarativeNodeListModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    Q_D(const DeclarativeNodeListModel);

    return d->rowCount();
}

/**
 * data
 */
QVariant DeclarativeNodeListModel::data(const QModelIndex &index, int role) const {
    Q_D(const DeclarativeNodeListModel);

    return d->data(index, role);
}

/**
 * data
 */
QVariant DeclarativeNodeListModel::data(int row, const QByteArray &role) const {
    Q_D(const DeclarativeNodeListModel);

    return d->data(row, role);
}

/**
 * get
 */
Node* DeclarativeNodeListModel::get(const QModelIndex &index) const {
    Q_D(const DeclarativeNodeListModel);

    return d->get(index);
}

/**
 * get
 */
Node* DeclarativeNodeListModel::get(int row) const {
    Q_D(const DeclarativeNodeListModel);

    return d->get(row);
}

/**
 * activeNode
 */
Node* DeclarativeNodeListModel::activeNode() const {
    Q_D(const DeclarativeNodeListModel);

    return d->activeNode();
}

/**
 * canPaste
 */
bool DeclarativeNodeListModel::canPaste() const {
    Q_D(const DeclarativeNodeListModel);

    return d->canPaste();
}

/**
 * status
 */
DeclarativeNodeListModel::Status DeclarativeNodeListModel::status() const {
    Q_D(const DeclarativeNodeListModel);

    return d->status();
}

/**
 * errorString
 */
QString DeclarativeNodeListModel::errorString() const {
    Q_D(const DeclarativeNodeListModel);

    return d->errorString();
}

/**
 * reload
 */
void DeclarativeNodeListModel::reload() {
    Q_D(DeclarativeNodeListModel);

    d->reload();
}

/**
 * clear
 */
void DeclarativeNodeListModel::clear() {
    Q_D(DeclarativeNodeListModel);

    d->clear();
}

/**
 * cd
 */
void DeclarativeNodeListModel::cd(int row) {
    Q_D(DeclarativeNodeListModel);

    d->cd(row);
}

/**
 * cd
 */
void DeclarativeNodeListModel::cd(const QString &resourcePath) {
    Q_D(DeclarativeNodeListModel);

    d->cd(resourcePath);
}

/**
 * cdUp
 */
void DeclarativeNodeListModel::cdUp() {
    Q_D(DeclarativeNodeListModel);

    d->cdUp();
}

/**
 * cdRoot
 */
void DeclarativeNodeListModel::cdRoot() {
    Q_D(DeclarativeNodeListModel);

    d->cdRoot();
}

/**
 * makeDirectory
 */
void DeclarativeNodeListModel::makeDirectory(const QString &name) {
    Q_D(DeclarativeNodeListModel);

    d->makeDirectory(name);
}

/**
 * renameNode
 */
void DeclarativeNodeListModel::renameNode(int row, const QString &name) {
    Q_D(DeclarativeNodeListModel);

    d->renameNode(row, name);
}

/**
 * cutNode
 */
void DeclarativeNodeListModel::cutNode(int row) {
    Q_D(DeclarativeNodeListModel);

    d->cutNode(row);
}

/**
 * pasteNode
 */
void DeclarativeNodeListModel::pasteNode() {
    Q_D(DeclarativeNodeListModel);

    d->pasteNode();
}

/**
 * deleteNode
 */
void DeclarativeNodeListModel::deleteNode(int row) {
    Q_D(DeclarativeNodeListModel);

    d->deleteNode(row);
}

/**
 * setFilePublic
 */
void DeclarativeNodeListModel::setFilePublic(int row, bool isPublic) {
    Q_D(DeclarativeNodeListModel);

    d->setFilePublic(row, isPublic);
}

#include "moc_declarativenodelistmodel.cpp"

}
