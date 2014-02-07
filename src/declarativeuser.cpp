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
 * \file declarativeuser.cpp
 */

#include "declarativeuser.h"
#include "declarativeuser_p.h"

namespace QtUbuntuOne {

DeclarativeUser::DeclarativeUser(QObject *parent) :
    QObject(parent),
    d_ptr(new DeclarativeUserPrivate(this))
{
}

DeclarativeUser::~DeclarativeUser() {}

/**
 * id
 */
QString DeclarativeUser::id() const {
    Q_D(const DeclarativeUser);

    return d->id();
}

/**
 * name
 */
QString DeclarativeUser::name() const {
    Q_D(const DeclarativeUser);

    return d->name();
}

/**
 * resourcePath
 */
QString DeclarativeUser::resourcePath() const {
    Q_D(const DeclarativeUser);

    return d->resourcePath();
}

/**
 * rootNodePath
 */
QString DeclarativeUser::rootNodePath() const {
    Q_D(const DeclarativeUser);

    return d->rootNodePath();
}

/**
 * userNodePaths
 */
QStringList DeclarativeUser::userNodePaths() const {
    Q_D(const DeclarativeUser);

    return d->userNodePaths();
}

/**
 * maxBytes
 */
qint64 DeclarativeUser::maxBytes() const {
    Q_D(const DeclarativeUser);

    return d->maxBytes();
}

/**
 * usedBytes
 */
qint64 DeclarativeUser::usedBytes() const {
    Q_D(const DeclarativeUser);

    return d->usedBytes();
}

/**
 * error
 */
DeclarativeUser::Error DeclarativeUser::error() const {
    Q_D(const DeclarativeUser);

    return d->error();
}

/**
 * errorString
 */
QString DeclarativeUser::errorString() const {
    Q_D(const DeclarativeUser);

    return d->errorString();
}

/**
 * load
 */
void DeclarativeUser::load() {
    Q_D(DeclarativeUser);

    d->load();
}

#include "moc_declarativeuser.cpp"

}
