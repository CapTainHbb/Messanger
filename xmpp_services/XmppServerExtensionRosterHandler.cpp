#include <XmppServerExtensionRosterHandler.hpp>

extern const char *ns_roster;

bool XmppServerExtensionRosterHandler::handleStanza(const QDomElement &stanza)
{

    if(!QXmppRosterIq::isRosterIq(stanza))
    {
        return false;
    }

    QXmppIq iq{ };
    iq.parse(stanza);
    QDomElement queryElement = stanza.firstChildElement(QStringLiteral("query"));
    return handleQueryElement(queryElement, iq);
}

bool XmppServerExtensionRosterHandler::handleQueryElement(const QDomElement& query_element, const QXmppIq& iq)
{

    if(query_element.namespaceURI() != QString(ns_roster))
    {
        return false;
    }

    switch (iq.type())
    {
        case QXmppIq::Type::Set:
        {
            return handleSetRoster(query_element, iq);
        }
        case QXmppIq::Type::Get:
        {
            return handleGetRoster(query_element, iq);
        }
        default:
        {
            qDebug() << "unsupported roster Iq " << static_cast<int>(iq.type());
            return false;
        }
    }
}

bool XmppServerExtensionRosterHandler::handleSetRoster(const QDomElement& query_element, const QXmppIq& iq)
{
    QDomElement itemElement = query_element.firstChildElement(QStringLiteral("item"));
    QString sender_username{ iq.from().split('@').at(0) };

    while (!itemElement.isNull()) {

        QXmppRosterIq::Item item;
        item.parse(itemElement);
        if("captainhb" == sender_username)
        {
            captainhb_rosters.addItem(item);
        }
        else if("ahmad" == sender_username)
        {
            ahmad_rosters.addItem(item);
        }
        itemElement = itemElement.nextSiblingElement(QStringLiteral("item"));
    }

    sendSetRosterIqResult(sender_username, iq);

    return true;
}

void XmppServerExtensionRosterHandler::sendSetRosterIqResult(const QString& sender_name, const QXmppIq& iq)
{
    QXmppIq result;
    result.setType(QXmppIq::Type::Result);
    result.setTo(iq.from());
    result.setFrom( sender_name + "@" + "127.0.0.1");
    result.setId(iq.id());
    server()->sendPacket(result);
}


bool XmppServerExtensionRosterHandler::handleGetRoster(const QDomElement& query_element, const QXmppIq& iq)
{
    QString sender_username{ iq.from().split('@').at(0) };

    if("ahmad" == sender_username)
    {
        sendGetRosterIqResult(ahmad_rosters, iq);
    }
    else if ("captainhb" == sender_username)
    {
        sendGetRosterIqResult(captainhb_rosters, iq);
    }
    else
    {
        qDebug() << "sender not found " << sender_username;
        return false;
    }

    return true;
}

void XmppServerExtensionRosterHandler::sendGetRosterIqResult(QXmppRosterIq &roster_iq, const QXmppIq& iq)
{
    QString sender_username{ iq.from().split('@').at(0) };
    roster_iq.setFrom(sender_username + "@" + "127.0.0.1");
    roster_iq.setId(iq.id());
    roster_iq.setTo(iq.from());
    roster_iq.setType(QXmppIq::Type::Result);
    server()->sendPacket(roster_iq);
}
