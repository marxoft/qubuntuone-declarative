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

#include "declarativetoken_p.h"
#include "authentication.h"

namespace QtUbuntuOne {

DeclarativeTokenPrivate::DeclarativeTokenPrivate(DeclarativeToken *parent) :
    q_ptr(parent),
    m_error(DeclarativeToken::NoError)
{
}

DeclarativeTokenPrivate::~DeclarativeTokenPrivate() {}

QString DeclarativeTokenPrivate::tokenName() const {
    return m_tokenName;
}

void DeclarativeTokenPrivate::setTokenName(const QString &name) {
    m_tokenName = name;
}

QString DeclarativeTokenPrivate::consumerKey() const {
    return Authentication::consumerKey();
}

void DeclarativeTokenPrivate::setConsumerKey(const QString &key) {
    Q_Q(DeclarativeToken);

    if (key != this->consumerKey()) {
        Authentication::setConsumerKey(key);
        emit q->consumerKeyChanged(key);
        emit q->isEmptyChanged(this->isEmpty());
    }
}

QString DeclarativeTokenPrivate::consumerSecret() const {
    return Authentication::consumerSecret();
}

void DeclarativeTokenPrivate::setConsumerSecret(const QString &secret) {
    Q_Q(DeclarativeToken);

    if (secret != this->consumerSecret()) {
        Authentication::setConsumerSecret(secret);
        emit q->consumerSecretChanged(secret);
        emit q->isEmptyChanged(this->isEmpty());
    }
}

QString DeclarativeTokenPrivate::tokenKey() const {
    return Authentication::tokenKey();
}

void DeclarativeTokenPrivate::setTokenKey(const QString &key) {
    Q_Q(DeclarativeToken);

    if (key != this->tokenKey()) {
        Authentication::setTokenKey(key);
        emit q->tokenKeyChanged(key);
        emit q->isEmptyChanged(this->isEmpty());
    }
}

QString DeclarativeTokenPrivate::tokenSecret() const {
    return Authentication::tokenSecret();
}

void DeclarativeTokenPrivate::setTokenSecret(const QString &secret) {
    Q_Q(DeclarativeToken);

    if (secret != this->tokenSecret()) {
        Authentication::setTokenSecret(secret);
        emit q->tokenSecretChanged(secret);
        emit q->isEmptyChanged(this->isEmpty());
    }
}

DeclarativeToken::Error DeclarativeTokenPrivate::error() const {
    return m_error;
}

void DeclarativeTokenPrivate::setError(DeclarativeToken::Error error) {
    m_error = error;
}

QString DeclarativeTokenPrivate::errorString() const {
    return m_errorString;
}

void DeclarativeTokenPrivate::setErrorString(const QString &errorString) {
    m_errorString = errorString;
}

bool DeclarativeTokenPrivate::isEmpty() const {
    return (this->consumerKey().isEmpty()) && (this->tokenSecret().isEmpty())
            && (this->tokenKey().isEmpty()) && (this->tokenSecret().isEmpty());
}

void DeclarativeTokenPrivate::authenticate(const QString &email, const QString &password, const QString &applicationName) {
    Q_Q(DeclarativeToken);

    Token *token = Authentication::authenticate(email, password, applicationName);
    q->connect(token, SIGNAL(ready(Token*)), q, SLOT(_q_onTokenReady(Token*)));
}

void DeclarativeTokenPrivate::authenticate(const QString &email, const QString &password, const QString &oneTimePassword, const QString &applicationName) {
    Q_Q(DeclarativeToken);

    Token *token = Authentication::authenticate(email, password, oneTimePassword, applicationName);
    q->connect(token, SIGNAL(ready(Token*)), q, SLOT(_q_onTokenReady(Token*)));
}

void DeclarativeTokenPrivate::clear() {
    this->setConsumerKey(QString());
    this->setConsumerSecret(QString());
    this->setTokenKey(QString());
    this->setTokenSecret(QString());
}

void DeclarativeTokenPrivate::_q_onTokenReady(Token *token) {
    Q_Q(DeclarativeToken);

    this->setError(DeclarativeToken::Error(token->error()));
    this->setErrorString(token->errorString());

    switch (this->error()) {
    case DeclarativeToken::NoError:
        this->setTokenName(token->tokenName());
        this->setConsumerKey(token->consumerKey());
        this->setConsumerSecret(token->consumerSecret());
        this->setTokenKey(token->tokenKey());
        this->setTokenSecret(token->tokenSecret());
        break;
    default:
        break;
    }

    token->deleteLater();

    emit q->ready();
}

}
