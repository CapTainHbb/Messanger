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

bool XmppServerExtensionRosterHandler::handleQueryElement(const QDomElement& query_element, QXmppIq& iq)
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

bool XmppServerExtensionRosterHandler::handleSetRoster(const QDomElement& query_element, QXmppIq& iq)
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

    sendIq(iq, sender_username, QXmppIq::Type::Result);

    captainhb_rosters.setId(iq.id());
    sendIq(captainhb_rosters,sender_username, QXmppIq::Type::Set);

    return true;
}

bool XmppServerExtensionRosterHandler::handleGetRoster(const QDomElement& query_element, QXmppIq& iq)
{
    QString sender_username{ iq.from().split('@').at(0) };

    if("ahmad" == sender_username)
    {
        ahmad_rosters.setId(iq.id());
        sendIq(ahmad_rosters, sender_username , QXmppIq::Type::Result);
    }
    else if ("captainhb" == sender_username)
    {
        captainhb_rosters.setId(iq.id());
        sendIq(captainhb_rosters, sender_username , QXmppIq::Type::Result);
    }
    else
    {
        qDebug() << "sender not found " << sender_username;
        return false;
    }

    return true;
}

