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
 * \file declarativetoken.h
 */

#ifndef DECLARATIVETOKEN_H
#define DECLARATIVETOKEN_H

#include "token.h"
#include <QObject>

namespace QtUbuntuOne {

class DeclarativeTokenPrivate;

/**
 * \class DeclarativeToken
 * \brief Handles Ubuntu One authentication.
 *
 * DeclarativeToken handles all Ubuntu One authentication.
 */
class Q_DECL_EXPORT DeclarativeToken : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString tokenName
               READ tokenName
               NOTIFY ready)
    Q_PROPERTY(QString consumerKey
               READ consumerKey
               WRITE setConsumerKey
               NOTIFY consumerKeyChanged)
    Q_PROPERTY(QString consumerSecret
               READ consumerSecret
               WRITE setConsumerSecret
               NOTIFY consumerSecretChanged)
    Q_PROPERTY(QString tokenKey
               READ tokenKey
               WRITE setTokenKey
               NOTIFY tokenKeyChanged)
    Q_PROPERTY(QString tokenSecret
               READ tokenSecret
               WRITE setTokenSecret
               NOTIFY tokenSecretChanged)
    Q_PROPERTY(Error error
               READ error
               NOTIFY ready)
    Q_PROPERTY(QString errorString
               READ errorString
               NOTIFY ready)
    Q_PROPERTY(bool isEmpty
               READ isEmpty
               NOTIFY isEmptyChanged)

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

    explicit DeclarativeToken(QObject *parent = 0);
    ~DeclarativeToken();
    
    /**
     * Returns the token name.
     *
     * \return QString The token name.
     */
    QString tokenName() const;

    /**
     * Returns the OAuth consumer key used for signing requests to the Ubuntu One API.
     *
     * \return QString The consumer key.
     */
    QString consumerKey() const;

    /**
     * Sets the OAuth consumer key used for signing requests to the Ubuntu One API.
     *
     * \param key The consumer key.
     */
    void setConsumerKey(const QString &key);

    /**
     * Returns the OAuth consumer secret used for signing requests to the Ubuntu One API.
     *
     * \return QString The consumer secret.
     */
    QString consumerSecret() const;

    /**
     * Sets the OAuth consumer secret used for signing requests to the Ubuntu One API.
     *
     * \param secret The consumer secret.
     */
    void setConsumerSecret(const QString &secret);

    /**
     * Returns the OAuth token key used for signing requests to the Ubuntu One API.
     *
     * \return QString The token key.
     */
    QString tokenKey() const;

    /**
     * Sets the OAuth token key used for signing requests to the Ubuntu One API.
     *
     * \param key The token key.
     */
    void setTokenKey(const QString &key);

    /**
     * Returns the OAuth token secret used for signing requests to the Ubuntu One API.
     *
     * \return QString The token secret.
     */
    QString tokenSecret() const;

    /**
     * Sets the OAuth token secret used for signing requests to the Ubuntu One API.
     *
     * \param secret The token secret.
     */
    void setTokenSecret(const QString &secret);

    /**
     * Returns the error resulting from the authentication request, or NoError if no error was reported.
     *
     * \return Error The request error.
     */
    Error error() const;

    /**
     * Returns a human-readable string detailing the error resulting from the authentication request, or an empty string if no error was reported.
     *
     * \return QString The request error string.
     */
    QString errorString() const;

    /**
     * Returns true if all credentials are empty.
     *
     * \return bool
     */
    bool isEmpty() const;

    /**
     * Performs an authentication request using the supplied credentials.
     *
     * \param email The email address of the user.
     * \param password The password of the user.
     * \param applicationName The name of the application requesting authorisation.
     */
    Q_INVOKABLE void authenticate(const QString &email, const QString &password, const QString &applicationName);

    /**
     * Overloaded method. Performs an authentication request using the supplied credentials.
     * Only use this method if the user supplies a one-time password.
     *
     * \param email The email address of the user.
     * \param password The password of the user.
     * \param oneTimePassword The one-time password of the user.
     * \param applicationName The name of the application requesting authorisation.
     */
    Q_INVOKABLE void authenticate(const QString &email, const QString &password, const QString &oneTimePassword, const QString &applicationName);

    /**
     * A convenience method that clears the credentials.
     */
    Q_INVOKABLE void clear();

signals:
    /**
     * Emitted when the request is completed.
     */
    void ready();

    /**
     * Emitted when the consumer key changes.
     */
    void consumerKeyChanged(const QString &key);

    /**
     * Emitted when the consumer secret changes.
     */
    void consumerSecretChanged(const QString &secret);

    /**
     * Emitted when the token key changes.
     */
    void tokenKeyChanged(const QString &key);

    /**
     * Emitted when the token secret changes.
     */
    void tokenSecretChanged(const QString &secret);

    /**
     * Emitted when the any of the credentials change.
     */
    void isEmptyChanged(bool empty);

private:
    QScopedPointer<DeclarativeTokenPrivate> d_ptr;
    
    Q_DECLARE_PRIVATE(DeclarativeToken)

    Q_PRIVATE_SLOT(d_func(), void _q_onTokenReady(Token *token))

};

}

Q_DECLARE_METATYPE(QtUbuntuOne::DeclarativeToken::Error)

#endif // DECLARATIVETOKEN_H
