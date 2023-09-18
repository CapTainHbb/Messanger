#include <XmppServerExtensionRosterHandler.hpp>

bool XmppServerExtensionRosterHandler::handleStanza(const QDomElement &stanza)
{
    if(stanza.hasAttribute("type"))
    {
        QString attribute_value{ stanza.attribute("type") };
        if("set" == attribute_value)
        {
            QDomNodeList nodes = stanza.elementsByTagName("item");
            for(int i = 0; i < nodes.count(); i++)
            {
                QDomNode elm = nodes.at(i);
                if(elm.isElement())
                {
                    auto item_element = elm.toElement();
                    qDebug() << item_element.tagName()
                             << " = "
                             <<  item_element.text();
                    if(item_element.hasAttribute("jid"))
                    {
                        qDebug() << item_element.attribute("jid");
                    }
                }
            }
        }
    }
    return false;
}
