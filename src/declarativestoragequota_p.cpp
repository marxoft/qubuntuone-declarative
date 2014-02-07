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

#include "declarativestoragequota_p.h"
#include "account.h"

namespace QtUbuntuOne {

DeclarativeStorageQuotaPrivate::DeclarativeStorageQuotaPrivate(DeclarativeStorageQuota *parent) :
    q_ptr(parent),
    m_error(DeclarativeStorageQuota::NoError)
{
}

DeclarativeStorageQuotaPrivate::~DeclarativeStorageQuotaPrivate() {}

qint64 DeclarativeStorageQuotaPrivate::totalStorage() const {
    return m_maxStorage;
}

void DeclarativeStorageQuotaPrivate::setTotalStorage(qint64 max) {
    m_maxStorage = max;
}

qint64 DeclarativeStorageQuotaPrivate::usedStorage() const {
    return m_usedStorage;
}

void DeclarativeStorageQuotaPrivate::setUsedStorage(qint64 used) {
    m_usedStorage = used;
}

DeclarativeStorageQuota::Error DeclarativeStorageQuotaPrivate::error() const {
    return m_error;
}

void DeclarativeStorageQuotaPrivate::setError(DeclarativeStorageQuota::Error error) {
    m_error = error;
}

QString DeclarativeStorageQuotaPrivate::errorString() const {
    return m_errorString;
}

void DeclarativeStorageQuotaPrivate::setErrorString(const QString &errorString) {
    m_errorString = errorString;
}

void DeclarativeStorageQuotaPrivate::load() {
    Q_Q(DeclarativeStorageQuota);

    StorageQuota *quota = Account::getStorageQuota();
    q->connect(quota, SIGNAL(ready(StorageQuota*)), q, SLOT(_q_onQuotaReady(StorageQuota*)));
}

void DeclarativeStorageQuotaPrivate::_q_onQuotaReady(StorageQuota *quota) {
    Q_Q(DeclarativeStorageQuota);

    this->setError(DeclarativeStorageQuota::Error(quota->error()));
    this->setErrorString(quota->errorString());

    switch (this->error()) {
    case DeclarativeStorageQuota::NoError:
        this->setTotalStorage(quota->totalStorage());
        this->setUsedStorage(quota->usedStorage());
        break;
    default:
        break;
    }

    quota->deleteLater();

    emit q->ready();
}

}
