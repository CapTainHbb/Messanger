#pragma once

#include <QXmppServer.h>
#include <QXmppServerExtension.h>
#include <QDomElement>

class XmppServerExtensionRosterHandler : public QXmppServerExtension
{
public:
    XmppServerExtensionRosterHandler() = default;
    ~XmppServerExtensionRosterHandler() = default;

    virtual bool handleStanza(const QDomElement &stanza);
};
