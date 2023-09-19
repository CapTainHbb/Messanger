#pragma once

#include <QXmppServer.h>
#include <QXmppServerExtension.h>
#include <QDomElement>
#include <QXmppIq.h>
#include <QXmppRosterIq.h>

class XmppServerExtensionRosterHandler : public QXmppServerExtension
{
public:
    XmppServerExtensionRosterHandler() = default;
    ~XmppServerExtensionRosterHandler() = default;

    virtual bool handleStanza(const QDomElement &stanza);

protected:
    virtual bool handleQueryElement(const QDomElement& query_element, const QXmppIq& iq);

    virtual bool handleSetRoster(const QDomElement& query_element, const QXmppIq& iq);
    virtual void sendSetRosterIqResult(const QString& sender_name, const QXmppIq& iq);
    virtual bool handleGetRoster(const QDomElement& query_element, const QXmppIq& iq);
    virtual void sendGetRosterIqResult(QXmppRosterIq& roster_iq, const QXmppIq& iq);

private:
    QXmppRosterIq captainhb_rosters{ };
    QXmppRosterIq ahmad_rosters{ };
};
