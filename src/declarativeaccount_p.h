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

#ifndef DECLARATIVEACCOUNT_P_H
#define DECLARATIVEACCOUNT_P_H

#include "declarativeaccount.h"
#include <QStringList>

namespace QtUbuntuOne {

class DeclarativeAccountPrivate
{

public:
    DeclarativeAccountPrivate(DeclarativeAccount *parent);
    virtual ~DeclarativeAccountPrivate();

    QString id() const;

    QString username() const;

    QString nickname() const;

    QString firstName() const;

    QString lastName() const;

    QString email() const;

    QString openId() const;

    qint64 totalStorage() const;

    QString currentPlan() const;

    QVariantList detailedPlans() const;

    QStringList features() const;

    QVariantMap subscription() const;

    DeclarativeAccount::Error error() const;
    QString errorString() const;

    void load();

private:
    void setId(const QString &path);

    void setUsername(const QString &name);

    void setNickname(const QString &name);

    void setFirstName(const QString &name);

    void setLastName(const QString &name);

    void setEmail(const QString &email);

    void setOpenId(const QString &id);

    void setTotalStorage(qint64 bytes);

    void setCurrentPlan(const QString &plan);

    void setDetailedPlans(const QVariantList &plans);

    void setFeatures(const QStringList &features);

    void setSubscription(const QVariantMap &subscription);

    void setError(DeclarativeAccount::Error error);
    void setErrorString(const QString &errorString);

    void _q_onAccountReady(UserAccount *account);

    DeclarativeAccount *q_ptr;

    QString m_id;

    QString m_username;

    QString m_nickname;

    QString m_firstName;

    QString m_lastName;

    QString m_email;

    QString m_openId;

    qint64 m_totalStorage;

    QString m_currentPlan;

    QVariantList m_detailedPlans;

    QStringList m_features;

    QVariantMap m_subscription;

    DeclarativeAccount::Error m_error;
    QString m_errorString;

    Q_DECLARE_PUBLIC(DeclarativeAccount)
};

}

#endif // DECLARATIVEACCOUNT_P_H
