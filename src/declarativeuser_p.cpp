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

#include "declarativeuser_p.h"
#include "files.h"

namespace QtUbuntuOne {

DeclarativeUserPrivate::DeclarativeUserPrivate(DeclarativeUser *parent) :
    q_ptr(parent),
    m_error(DeclarativeUser::NoError)
{
}

DeclarativeUserPrivate::~DeclarativeUserPrivate() {}

QString DeclarativeUserPrivate::id() const {
    return m_id;
}

void DeclarativeUserPrivate::setId(const QString &id) {
    m_id = id;
}

QString DeclarativeUserPrivate::name() const {
    return m_name;
}

void DeclarativeUserPrivate::setName(const QString &name) {
    m_name = name;
}

QString DeclarativeUserPrivate::resourcePath() const {
    return m_resourcePath;
}

void DeclarativeUserPrivate::setResourcePath(const QString &path) {
    m_resourcePath = path;
}

QString DeclarativeUserPrivate::rootNodePath() const {
    return m_rootNodePath;
}

void DeclarativeUserPrivate::setRootNodePath(const QString &path) {
    m_rootNodePath = path;
}

QStringList DeclarativeUserPrivate::userNodePaths() const {
    return m_userNodePaths;
}

void DeclarativeUserPrivate::setUserNodePaths(const QStringList &paths) {
    m_userNodePaths = paths;
}

qint64 DeclarativeUserPrivate::maxBytes() const {
    return m_maxBytes;
}

void DeclarativeUserPrivate::setMaxBytes(qint64 bytes) {
    m_maxBytes = bytes;
}

qint64 DeclarativeUserPrivate::usedBytes() const {
    return m_usedBytes;
}

void DeclarativeUserPrivate::setUsedBytes(qint64 bytes) {
    m_usedBytes = bytes;
}

DeclarativeUser::Error DeclarativeUserPrivate::error() const {
    return m_error;
}

void DeclarativeUserPrivate::setError(DeclarativeUser::Error error) {
    m_error = error;
}

QString DeclarativeUserPrivate::errorString() const {
    return m_errorString;
}

void DeclarativeUserPrivate::setErrorString(const QString &errorString) {
    m_errorString = errorString;
}

void DeclarativeUserPrivate::load() {
    Q_Q(DeclarativeUser);

    User *user = Files::getUser();
    q->connect(user, SIGNAL(ready(User*)), q, SLOT(_q_onUserReady(User*)));
}

void DeclarativeUserPrivate::_q_onUserReady(User *user) {
    Q_Q(DeclarativeUser);

    this->setError(DeclarativeUser::Error(user->error()));
    this->setErrorString(user->errorString());

    switch (this->error()) {
    case DeclarativeUser::NoError:
        this->setId(user->id());
        this->setName(user->name());
        this->setResourcePath(user->resourcePath());
        this->setRootNodePath(user->rootNodePath());
        this->setUserNodePaths(user->userNodePaths());
        this->setMaxBytes(user->maxBytes());
        this->setUsedBytes(user->usedBytes());
        break;
    default:
        break;
    }

    user->deleteLater();

    emit q->ready();
}

}
