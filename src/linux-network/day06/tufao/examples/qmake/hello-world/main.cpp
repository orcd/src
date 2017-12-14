/*
  Copyright (c) 2012 Vinícius dos Santos Oliveira

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
  */

#include <QCoreApplication>
#include <Tufao/HttpServer>
#include <QtCore/QUrl>
#include <Tufao/HttpServerRequest>
#include <Tufao/Headers>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

// http://xueguoliang.cn/user
// {
//      cmd: "login",
//      username: "aaa",
//      password: "bbb",
//      logintype: "driver"
// }

#if 0
        if (req.method() == "POST") {
            QObject::connect(&req, &HttpServerRequest::end, [&req,&res]() {
                res.writeHead(Tufao::HttpResponseStatus::OK);
                res.headers().insert("Content-Type", "text/plain");
                res.end(req.readBody());
            });
            return;
        }
#endif

void postDataReady(Tufao::HttpServerRequest& req,
                  Tufao::HttpServerResponse& resp)
{
    QString path = req.url().path().toUtf8();

    QByteArray postData = req.readBody();
    if(path == "/order")
    {
        resp.end("cmd is order, postData is " + postData + "\n");
    }
    else if(path == "/user")
    {
        {
            QJsonDocument doc = QJsonDocument::fromJson(postData);
            QJsonObject obj = doc.object();
            qDebug() << obj.value("username") << obj.value("password") << obj.value("cmd") << obj.value("logintype");
        }
        // {result: "OK"}
        QJsonObject obj;
        obj.insert("result", QString("OK"));
        QJsonDocument doc(obj);
        QByteArray respJson = doc.toJson();

        resp.end(respJson);
    }
    else
    {
        resp.end("unkdown request\n");
    }

}

void response(Tufao::HttpServerRequest& req, 
        Tufao::HttpServerResponse& resp)
{
    resp.writeHead(Tufao::HttpResponseStatus::OK); // 200 OK
    resp.headers().replace("Content-Type", "text/html");

    if(req.method() != "POST")
    {
        resp.end("NEED POST METHOD");
        return;    
    }

    QObject::connect(&req, &Tufao::HttpServerRequest::end, [&req, &resp](){
    
     postDataReady(req, resp);
                
            });

}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Tufao::HttpServer server;

    QObject::connect(&server, &Tufao::HttpServer::requestReady,
                     [](Tufao::HttpServerRequest &req,
                        Tufao::HttpServerResponse &resp) 
                     {
                         response(req, resp);
                        // response.writeHead(Tufao::HttpResponseStatus::OK);
                        // response.headers().replace("Content-Type", "text/plain");
//                         response.end("Hello from xueguoliang.cn " + request.url().path().toUtf8());
                 //       response.end("Hello from server");
                // QString path = request.url().path().toUtf8();
                // if(path == "user")
                  //  response.end
                     });

    server.listen(QHostAddress::Any, 11111);

    return a.exec();
}
