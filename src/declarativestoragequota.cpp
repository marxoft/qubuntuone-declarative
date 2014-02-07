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
 * \file declarativestoragequota.cpp
 */

#include "declarativestoragequota.h"
#include "declarativestoragequota_p.h"

namespace QtUbuntuOne {

DeclarativeStorageQuota::DeclarativeStorageQuota(QObject *parent) :
    QObject(parent),
    d_ptr(new DeclarativeStorageQuotaPrivate(this))
{
}

DeclarativeStorageQuota::~DeclarativeStorageQuota() {}

/**
 * totalStorage
 */
qint64 DeclarativeStorageQuota::totalStorage() const {
    Q_D(const DeclarativeStorageQuota);

    return d->totalStorage();
}

/**
 * usedStorage
 */
qint64 DeclarativeStorageQuota::usedStorage() const {
    Q_D(const DeclarativeStorageQuota);

    return d->usedStorage();
}

/**
 * error
 */
DeclarativeStorageQuota::Error DeclarativeStorageQuota::error() const {
    Q_D(const DeclarativeStorageQuota);

    return d->error();
}

/**
 * errorString
 */
QString DeclarativeStorageQuota::errorString() const {
    Q_D(const DeclarativeStorageQuota);

    return d->errorString();
}

/**
 * load
 */
void DeclarativeStorageQuota::load() {
    Q_D(DeclarativeStorageQuota);

    d->load();
}

#include "moc_declarativestoragequota.cpp"

}
