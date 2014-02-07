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
 * \file declarativeuser.h
 */

#ifndef DECLARATIVEUSER_H
#define DECLARATIVEUSER_H

#include "user.h"
#include <QObject>

namespace QtUbuntuOne {

class DeclarativeUserPrivate;

class Q_DECL_EXPORT DeclarativeUser : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString id
               READ id
               NOTIFY ready)
    Q_PROPERTY(QString name
               READ name
               NOTIFY ready)
    Q_PROPERTY(QString resourcePath
               READ resourcePath
               NOTIFY ready)
    Q_PROPERTY(QString rootNodePath
               READ rootNodePath
               NOTIFY ready)
    Q_PROPERTY(QStringList userNodePaths
               READ userNodePaths
               NOTIFY ready)
    Q_PROPERTY(qint64 maxBytes
               READ maxBytes
               NOTIFY ready)
    Q_PROPERTY(qint64 usedBytes
               READ usedBytes
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

    explicit DeclarativeUser(QObject *parent = 0);
    ~DeclarativeUser();
    
    /**
     * Returns the unique id of the User.
     *
     * \return QString
     */
    QString id() const;

    /**
     * Returns the name of the User.
     *
     * \return QString
     */
    QString name() const;

    /**
     * Returns the resource path of the User.
     *
     * \return QString
     */
    QString resourcePath() const;

    /**
     * Returns the root node path of the User.
     *
     * \return QString
     */
    QString rootNodePath() const;

    /**
     * Returns a list of user node paths of the User.
     *
     * \return QStringList
     */
    QStringList userNodePaths() const;

    /**
     * Returns the maximum storage of the User.
     *
     * \return qint64
     */
    qint64 maxBytes() const;

    /**
     * Returns the used storage of the User.
     *
     * \return qint64
     */
    qint64 usedBytes() const;

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
    QScopedPointer<DeclarativeUserPrivate> d_ptr;

    Q_DECLARE_PRIVATE(DeclarativeUser)

    Q_PRIVATE_SLOT(d_func(), void _q_onUserReady(User *user))
};

}

Q_DECLARE_METATYPE(QtUbuntuOne::DeclarativeUser::Error)

#endif // DECLARATIVEUSER_H
