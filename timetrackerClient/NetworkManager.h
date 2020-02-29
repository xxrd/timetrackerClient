#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>

class NetworkManager : public QNetworkAccessManager
{
private:
    QString token;

public:
    QNetworkRequest getRequest(QString url);
    void signup(QString name, QString email, QString pass1, QString pass2, std::function<void(QJsonDocument&)> func);
    void login(QString name, QString email, QString pass, std::function<void(QJsonDocument&)> func);
    void logout(void func(QNetworkReply* reply));
    void sendGet(QString url, std::function<void(QNetworkReply*)> func);
    void sendPost(QString url, QJsonDocument& body, std::function<void(QNetworkReply*)> func);
    void sendPut(QString url, QJsonDocument& body, std::function<void(QNetworkReply*)> func);
    void sendDelete(QString url, std::function<void(QNetworkReply*)> func);
};
#endif // NETWORKMANAGER_H
