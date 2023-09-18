#include <XmppServer.hpp>
#include <QCoreApplication>

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    XmppServer server("127.0.0.1");

    app.exec();
}
