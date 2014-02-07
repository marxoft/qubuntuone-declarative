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

#ifndef DECLARATIVETOKEN_P_H
#define DECLARATIVETOKEN_P_H

#include "declarativetoken.h"

namespace QtUbuntuOne {

class DeclarativeTokenPrivate
{

public:
    DeclarativeTokenPrivate(DeclarativeToken *parent);
    virtual ~DeclarativeTokenPrivate();

    QString tokenName() const;

    QString consumerKey() const;
    void setConsumerKey(const QString &key);

    QString consumerSecret() const;
    void setConsumerSecret(const QString &secret);

    QString tokenKey() const;
    void setTokenKey(const QString &key);

    QString tokenSecret() const;
    void setTokenSecret(const QString &secret);

    DeclarativeToken::Error error() const;
    QString errorString() const;

    bool isEmpty() const;

    void authenticate(const QString &email, const QString &password, const QString &applicationName);
    void authenticate(const QString &email, const QString &password, const QString &oneTimePassword, const QString &applicationName);

    void clear();

private:
    void _q_onTokenReady(Token *token);

    void setTokenName(const QString &name);

    void setError(DeclarativeToken::Error error);
    void setErrorString(const QString &errorString);

    DeclarativeToken *q_ptr;

    QString m_tokenName;

    DeclarativeToken::Error m_error;
    QString m_errorString;

    Q_DECLARE_PUBLIC(DeclarativeToken)
};

}

#endif // DECLARATIVETOKEN_P_H
