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

#include "declarativeaccount_p.h"
#include "account.h"

namespace QtUbuntuOne {

DeclarativeAccountPrivate::DeclarativeAccountPrivate(DeclarativeAccount *parent) :
    q_ptr(parent),
    m_error(DeclarativeAccount::NoError)
{
}

DeclarativeAccountPrivate::~DeclarativeAccountPrivate() {}

QString DeclarativeAccountPrivate::id() const {
    return m_id;
}

void DeclarativeAccountPrivate::setId(const QString &id) {
    m_id = id;
}

QString DeclarativeAccountPrivate::username() const {
    return m_username;
}

void DeclarativeAccountPrivate::setUsername(const QString &name) {
    m_username = name;
}

QString DeclarativeAccountPrivate::nickname() const {
    return m_nickname;
}

void DeclarativeAccountPrivate::setNickname(const QString &name) {
    m_nickname = name;
}

QString DeclarativeAccountPrivate::firstName() const {
    return m_firstName;
}

void DeclarativeAccountPrivate::setFirstName(const QString &name) {
    m_firstName = name;
}

QString DeclarativeAccountPrivate::lastName() const {
    return m_lastName;
}

void DeclarativeAccountPrivate::setLastName(const QString &name) {
    m_lastName = name;
}

QString DeclarativeAccountPrivate::email() const {
    return m_email;
}

void DeclarativeAccountPrivate::setEmail(const QString &email) {
    m_email = email;
}

QString DeclarativeAccountPrivate::openId() const {
    return m_openId;
}

void DeclarativeAccountPrivate::setOpenId(const QString &id) {
    m_openId = id;
}

qint64 DeclarativeAccountPrivate::totalStorage() const {
    return m_totalStorage;
}

void DeclarativeAccountPrivate::setTotalStorage(qint64 bytes) {
    m_totalStorage = bytes;
}

QString DeclarativeAccountPrivate::currentPlan() const {
    return m_currentPlan;
}

void DeclarativeAccountPrivate::setCurrentPlan(const QString &plan) {
    m_currentPlan = plan;
}

QVariantList DeclarativeAccountPrivate::detailedPlans() const {
    return m_detailedPlans;
}

void DeclarativeAccountPrivate::setDetailedPlans(const QVariantList &plans) {
    m_detailedPlans = plans;
}

QStringList DeclarativeAccountPrivate::features() const {
    return m_features;
}

void DeclarativeAccountPrivate::setFeatures(const QStringList &features) {
    m_features = features;
}

QVariantMap DeclarativeAccountPrivate::subscription() const {
    return m_subscription;
}

void DeclarativeAccountPrivate::setSubscription(const QVariantMap &subscription) {
    m_subscription = subscription;
}

DeclarativeAccount::Error DeclarativeAccountPrivate::error() const {
    return m_error;
}

void DeclarativeAccountPrivate::setError(DeclarativeAccount::Error error) {
    m_error = error;
}

QString DeclarativeAccountPrivate::errorString() const {
    return m_errorString;
}

void DeclarativeAccountPrivate::setErrorString(const QString &errorString) {
    m_errorString = errorString;
}

void DeclarativeAccountPrivate::load() {
    Q_Q(DeclarativeAccount);

    UserAccount *account = Account::getAccount();
    q->connect(account, SIGNAL(ready(UserAccount*)), q, SLOT(_q_onAccountReady(UserAccount*)));
}

void DeclarativeAccountPrivate::_q_onAccountReady(UserAccount *account) {
    Q_Q(DeclarativeAccount);

    this->setError(DeclarativeAccount::Error(account->error()));
    this->setErrorString(account->errorString());

    switch (this->error()) {
    case DeclarativeAccount::NoError:
        this->setId(account->id());
        this->setUsername(account->username());
        this->setNickname(account->nickname());
        this->setFirstName(account->firstName());
        this->setLastName(account->lastName());
        this->setEmail(account->email());
        this->setOpenId(account->openId());
        this->setTotalStorage(account->totalStorage());
        this->setCurrentPlan(account->currentPlan());
        this->setDetailedPlans(account->detailedPlans());
        this->setFeatures(account->features());
        this->setSubscription(account->subscription());
        break;
    default:
        break;
    }

    account->deleteLater();

    emit q->ready();
}

}
