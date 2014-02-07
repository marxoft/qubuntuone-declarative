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

#include "declarativeaccount.h"
#include "declarativeaccount_p.h"

namespace QtUbuntuOne {

DeclarativeAccount::DeclarativeAccount(QObject *parent) :
    QObject(parent),
    d_ptr(new DeclarativeAccountPrivate(this))
{
}

DeclarativeAccount::~DeclarativeAccount() {}

/**
 * id
 */
QString DeclarativeAccount::id() const {
    Q_D(const DeclarativeAccount);

    return d->id();
}

/**
 * username
 */
QString DeclarativeAccount::username() const {
    Q_D(const DeclarativeAccount);

    return d->username();
}

/**
 * nickname
 */
QString DeclarativeAccount::nickname() const {
    Q_D(const DeclarativeAccount);

    return d->nickname();
}

/**
 * firstName
 */
QString DeclarativeAccount::firstName() const {
    Q_D(const DeclarativeAccount);

    return d->firstName();
}

/**
 * lastName
 */
QString DeclarativeAccount::lastName() const {
    Q_D(const DeclarativeAccount);

    return d->lastName();
}

/**
 * email
 */
QString DeclarativeAccount::email() const {
    Q_D(const DeclarativeAccount);

    return d->email();
}

/**
 * openId
 */
QString DeclarativeAccount::openId() const {
    Q_D(const DeclarativeAccount);

    return d->openId();
}

/**
 * totalStorage
 */
qint64 DeclarativeAccount::totalStorage() const {
    Q_D(const DeclarativeAccount);

    return d->totalStorage();
}

/**
 * currentPlan
 */
QString DeclarativeAccount::currentPlan() const {
    Q_D(const DeclarativeAccount);

    return d->currentPlan();
}

/**
 * detailedPlans
 */
QVariantList DeclarativeAccount::detailedPlans() const {
    Q_D(const DeclarativeAccount);

    return d->detailedPlans();
}

/**
 * features
 */
QStringList DeclarativeAccount::features() const {
    Q_D(const DeclarativeAccount);

    return d->features();
}

/**
 * subscription
 */
QVariantMap DeclarativeAccount::subscription() const {
    Q_D(const DeclarativeAccount);

    return d->subscription();
}

/**
 * error
 */
DeclarativeAccount::Error DeclarativeAccount::error() const {
    Q_D(const DeclarativeAccount);

    return d->error();
}

/**
 * errorString
 */
QString DeclarativeAccount::errorString() const {
    Q_D(const DeclarativeAccount);

    return d->errorString();
}

/**
 * load
 */
void DeclarativeAccount::load() {
    Q_D(DeclarativeAccount);

    d->load();
}

#include "moc_declarativeaccount.cpp"

}
