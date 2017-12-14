#include "server.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

Server::Server(QObject *parent) :
    QObject(parent)
{
    server = new Tufao::HttpServer();
    server->listen(QHostAddress::Any, 10098);
    connect(server, SIGNAL(requestReady(Tufao::HttpServerRequest&,Tufao::HttpServerResponse&)),
            this, SLOT(slotRequestReady(Tufao::HttpServerRequest&,Tufao::HttpServerResponse&)));

}

void Server::slotRequestReady(Tufao::HttpServerRequest &request, Tufao::HttpServerResponse &response)
{
    if(request.method() == "GET")
    {
        qDebug() << request.url();
        response.writeHead(Tufao::HttpResponseStatus::OK); // 200 OK
        response.end("hello from tufao");
    }
    else if(request.method() == "POST")
    {
        connect(&request, &Tufao::HttpServerRequest::end, [&](){
            response.writeHead(Tufao::HttpResponseStatus::OK);
            QByteArray jsonBuf = request.readBody();
#if 0

            QJsonDocument doc = QJsonDocument::fromJson(jsonBuf);
            QJsonObject root = doc.object();
            QJsonValue vUsername = root.value("username");
            QJsonValue vPassword = root.value("password");

            QString username = vUsername.toString();
            QString password = vPassword.toString();
#endif
            QJsonObject root = QJsonDocument::fromJson(jsonBuf).object();
            QString username = root.value("username").toString();
            QString password = root.value("password").toString();

            if(username == "zhangsan" && password == "haha")
            {
                response.end("login ok");
            }
            else
            {
                response.end("login error");
            }

            qDebug() << jsonBuf;


        });
    }
}
