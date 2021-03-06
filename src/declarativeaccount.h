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
 * \file declarativeaccount.h
 */

#ifndef DECLARATIVEACCOUNT_H
#define DECLARATIVEACCOUNT_H

#include "useraccount.h"
#include <QObject>

namespace QtUbuntuOne {

class DeclarativeAccountPrivate;

/**
 * \class DeclarativeAccount
 * \brief Contains the metadata of an UbuntuOne account.
 *
 * DeclarativeAccount contains the metadata of an UbuntuOne account.
 * The metadata is read-only.
 */
class Q_DECL_EXPORT DeclarativeAccount : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString id
               READ id
               NOTIFY ready)
    Q_PROPERTY(QString username
               READ username
               NOTIFY ready)
    Q_PROPERTY(QString nickname
               READ nickname
               NOTIFY ready)
    Q_PROPERTY(QString firstName
               READ firstName
               NOTIFY ready)
    Q_PROPERTY(QString lastName
               READ lastName
               NOTIFY ready)
    Q_PROPERTY(QString email
               READ email
               NOTIFY ready)
    Q_PROPERTY(QString openId
               READ openId
               NOTIFY ready)
    Q_PROPERTY(qint64 totalStorage
               READ totalStorage
               NOTIFY ready)
    Q_PROPERTY(QString currentPlan
               READ currentPlan
               NOTIFY ready)
    Q_PROPERTY(QVariantList detailedPlans
               READ detailedPlans
               NOTIFY ready)
    Q_PROPERTY(QStringList features
               READ features
               NOTIFY ready)
    Q_PROPERTY(QVariantMap subscription
               READ subscription
               NOTIFY ready)
    Q_PROPERTY(Error error
               READ error
               NOTIFY ready)
    Q_PROPERTY(QString errorString
               READ errorString
               NOTIFY ready)

    Q_ENUMS(Error)

public:
    /**
     * \enum Error
     */
    enum Error {
        NoError = QNetworkReply::NoError,
        ConnectionRefusedError = QNetworkReply::ConnectionRefusedError,
        RemoteHostClosedError = QNetworkReply::RemoteHostClosedError,
        HostNotFoundError = QNetworkReply::HostNotFoundError,
        TimeoutError = QNetworkReply::TimeoutError,
        OperationCanceledError = QNetworkReply::OperationCanceledError,
        SslHandshakeFailedError = QNetworkReply::SslHandshakeFailedError,
        TemporaryNetworkFailureError = QNetworkReply::TemporaryNetworkFailureError,
        ProxyConnectionRefusedError = QNetworkReply::ProxyConnectionRefusedError,
        ProxyConnectionClosedError = QNetworkReply::ProxyConnectionClosedError,
        ProxyNotFoundError = QNetworkReply::ProxyNotFoundError,
        ProxyTimeoutError = QNetworkReply::ProxyTimeoutError,
        ProxyAuthenticationRequiredError = QNetworkReply::ProxyAuthenticationRequiredError,
        ContentAccessDenied = QNetworkReply::ContentAccessDenied,
        ContentOperationNotPermittedError = QNetworkReply::ContentOperationNotPermittedError,
        ContentNotFoundError = QNetworkReply::ContentNotFoundError,
        AuthenticationRequiredError = QNetworkReply::AuthenticationRequiredError,
        ContentReSendError = QNetworkReply::ContentReSendError,
        ProtocolUnknownError = QNetworkReply::ProtocolUnknownError,
        ProtocolInvalidOperationError = QNetworkReply::ProtocolInvalidOperationError,
        UnknownNetworkError = QNetworkReply::UnknownNetworkError,
        UnknownProxyError = QNetworkReply::UnknownProxyError,
        UnknownContentError = QNetworkReply::UnknownContentError,
        ProtocolFailure = QNetworkReply::ProtocolFailure,
        ParserError = 1001
    };

    explicit DeclarativeAccount(QObject *parent = 0);
    ~DeclarativeAccount();

    /**
     * Returns the unique id of the UserAccount.
     *
     * \return QString
     */
    QString id() const;

    /**
     * Returns the username of the UserAccount.
     *
     * \return QString
     */
    QString username() const;

    /**
     * Returns the nickname of the UserAccount.
     *
     * \return QString
     */
    QString nickname() const;

    /**
     * Returns the first name of the UserAccount.
     *
     * \return QString
     */
    QString firstName() const;

    /**
     * Returns the last name of the UserAccount.
     *
     * \return QString
     */
    QString lastName() const;

    /**
     * Returns the email address of the UserAccount.
     *
     * \return QString
     */
    QString email() const;

    /**
     * Returns the open id of the UserAccount.
     *
     * \return QString
     */
    QString openId() const;

    /**
     * Returns the total storage of the UserAccount.
     *
     * \return qint64
     */
    qint64 totalStorage() const;

    /**
     * Returns the current plan of the UserAccount.
     *
     * \return QString
     */
    QString currentPlan() const;

    /**
     * Returns a list of plans of the UserAccount.
     *
     * \return QVariantList
     */
    QVariantList detailedPlans() const;

    /**
     * Returns a list of features of the UserAccount.
     *
     * \return QStringList
     */
    QStringList features() const;

    /**
     * Returns the subscription of the UserAccount.
     *
     * \return QVariantMap
     */
    QVariantMap subscription() const;

    /**
     * Returns the error resulting from the request, or NoError if no error was reported.
     *
     * \return Error The request error.
     */
    Error error() const;

    /**
     * Returns a human-readable string detailing the error resulting from the request, or an empty string if no error was reported.
     *
     * \return QString The request error string.
     */
    QString errorString() const;

    /**
     * Retrieves the metadata for the currently authenticated user.
     */
    Q_INVOKABLE void load();
    
signals:
    /**
     * Emitted when the request is completed.
     */
    void ready();

private:
    QScopedPointer<DeclarativeAccountPrivate> d_ptr;

    Q_DECLARE_PRIVATE(DeclarativeAccount)

    Q_PRIVATE_SLOT(d_func(), void _q_onAccountReady(UserAccount *account))
};

}

Q_DECLARE_METATYPE(QtUbuntuOne::DeclarativeAccount::Error)

#endif // DECLARATIVEACCOUNT_H
