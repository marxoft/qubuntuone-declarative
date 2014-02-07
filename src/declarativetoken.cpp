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
 * \file declarativetoken.cpp
 */

#include "declarativetoken.h"
#include "declarativetoken_p.h"
#include "authentication.h"

namespace QtUbuntuOne {

DeclarativeToken::DeclarativeToken(QObject *parent) :
    QObject(parent),
    d_ptr(new DeclarativeTokenPrivate(this))
{
}

DeclarativeToken::~DeclarativeToken() {}

/**
 * tokenName
 */
QString DeclarativeToken::tokenName() const {
    Q_D(const DeclarativeToken);

    return d->tokenName();
}

/**
 * consumerKey
 */
QString DeclarativeToken::consumerKey() const {
    Q_D(const DeclarativeToken);

    return d->consumerKey();
}

/**
 * setConsumerKey
 */
void DeclarativeToken::setConsumerKey(const QString &key) {
    Q_D(DeclarativeToken);

    d->setConsumerKey(key);
}

/**
 * consumerSecret
 */
QString DeclarativeToken::consumerSecret() const {
    Q_D(const DeclarativeToken);

    return d->consumerSecret();
}

/**
 * setConsumerSecret
 */
void DeclarativeToken::setConsumerSecret(const QString &secret) {
    Q_D(DeclarativeToken);

    d->setConsumerSecret(secret);
}

/**
 * tokenKey
 */
QString DeclarativeToken::tokenKey() const {
    Q_D(const DeclarativeToken);

    return d->tokenKey();
}

/**
 * setTokenKey
 */
void DeclarativeToken::setTokenKey(const QString &key) {
    Q_D(DeclarativeToken);

    d->setTokenKey(key);
}

/**
 * tokenSecret
 */
QString DeclarativeToken::tokenSecret() const {
    Q_D(const DeclarativeToken);

    return d->tokenSecret();
}

/**
 * setTokenSecret
 */
void DeclarativeToken::setTokenSecret(const QString &secret) {
    Q_D(DeclarativeToken);

    d->setTokenSecret(secret);
}

/**
 * error
 */
DeclarativeToken::Error DeclarativeToken::error() const {
    Q_D(const DeclarativeToken);

    return d->error();
}

/**
 * errorString
 */
QString DeclarativeToken::errorString() const {
    Q_D(const DeclarativeToken);

    return d->errorString();
}

/**
 * isEmpty
 */
bool DeclarativeToken::isEmpty() const {
    Q_D(const DeclarativeToken);

    return d->isEmpty();
}

/**
 * authenticate
 */
void DeclarativeToken::authenticate(const QString &email, const QString &password, const QString &applicationName) {
    Q_D(DeclarativeToken);

    d->authenticate(email, password, applicationName);
}

/**
 * authenticate
 */
void DeclarativeToken::authenticate(const QString &email, const QString &password, const QString &oneTimePassword, const QString &applicationName) {
    Q_D(DeclarativeToken);

    d->authenticate(email, password, oneTimePassword, applicationName);
}

/**
 * clear
 */
void DeclarativeToken::clear() {
    Q_D(DeclarativeToken);

    d->clear();
}

#include "moc_declarativetoken.cpp"

}
