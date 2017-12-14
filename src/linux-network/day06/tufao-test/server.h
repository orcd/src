#ifndef SERVER_H
#define SERVER_H

#include <QCoreApplication>
#include <tufao-1/Tufao/HttpServer>
#include <tufao-1/Tufao/HttpServerRequest>
#include <tufao-1/Tufao/HttpServerResponse>
#include <QDebug>
#include <QUrl>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);

    Tufao::HttpServer* server;

signals:

public slots:
    void slotRequestReady(Tufao::HttpServerRequest&,Tufao::HttpServerResponse&);

};

#endif // SERVER_H
