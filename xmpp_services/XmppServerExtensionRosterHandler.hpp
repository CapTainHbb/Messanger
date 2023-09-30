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
    virtual bool handleQueryElement(const QDomElement& query_element, QXmppIq& iq);

    virtual bool handleSetRoster(const QDomElement& query_element, QXmppIq& iq);
    virtual bool handleGetRoster(const QDomElement& query_element, QXmppIq& iq);

    template<typename T>
    void sendIq(T& iq, const QString& sender_name, QXmppIq::Type type)
    {
        iq.setFrom(sender_name + "@" + "127.0.0.1");
        iq.setId(iq.id());
        iq.setTo(iq.from());
        iq.setType(type);
        server()->sendPacket(iq);
    }

private:
    QXmppRosterIq captainhb_rosters{ };
    QXmppRosterIq ahmad_rosters{ };
};
