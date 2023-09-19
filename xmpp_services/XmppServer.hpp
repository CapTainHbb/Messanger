#pragma once

#include <QObject>
#include <QXmppQt6/QXmppServer.h>
#include <QXmppQt6/QXmppPasswordChecker.h>
#include <XmppServerExtensionRosterHandler.hpp>
#include <iostream>
#include <stdexcept>

#define USERNAME1 "ahmad"
#define PASSWORD1 "ahmad"

#define USERNAME2 "captainhb"
#define PASSWORD2 "captainhb"

class PasswordChecker : public QXmppPasswordChecker
{
    /// Retrieves the password for the given username.
    QXmppPasswordReply::Error getPassword(const QXmppPasswordRequest &request, QString &password) override
    {
        if (request.username() == USERNAME1) {
            password = PASSWORD1;
            return QXmppPasswordReply::NoError;
        }
        else if (USERNAME2 == request.username())
        {
            password = PASSWORD2;
            return QXmppPasswordReply::NoError;
        }
        else {
            return QXmppPasswordReply::AuthorizationError;
        }
    };

    /// Returns true as we implemented getPassword().
    bool hasGetPassword() const override
    {
        return true;
    };
};


class XmppServer : public QXmppServer
{
    Q_OBJECT

public:
    XmppServer(const QString& domain, QObject *parent = nullptr);
    ~XmppServer() = default;

private:
    PasswordChecker checker;
    QXmppLogger logger;
};