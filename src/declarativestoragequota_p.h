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

#ifndef DECLARATIVESTORAGEQUOTA_P_H
#define DECLARATIVESTORAGEQUOTA_P_H

#include "declarativestoragequota.h"

namespace QtUbuntuOne {

class DeclarativeStorageQuotaPrivate
{

public:
    DeclarativeStorageQuotaPrivate(DeclarativeStorageQuota *parent);
    virtual ~DeclarativeStorageQuotaPrivate();

    qint64 totalStorage() const;

    qint64 usedStorage() const;

    DeclarativeStorageQuota::Error error() const;
    QString errorString() const;

    void load();

private:
    void setTotalStorage(qint64 max);

    void setUsedStorage(qint64 used);

    void setError(DeclarativeStorageQuota::Error error);
    void setErrorString(const QString &errorString);

    void _q_onQuotaReady(StorageQuota *quota);

    DeclarativeStorageQuota *q_ptr;

    qint64 m_maxStorage;

    qint64 m_usedStorage;

    DeclarativeStorageQuota::Error m_error;
    QString m_errorString;

    Q_DECLARE_PUBLIC(DeclarativeStorageQuota)
};

}

#endif // DECLARATIVESTORAGEQUOTA_P_H
