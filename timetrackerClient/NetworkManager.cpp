#include "NetworkManager.h"
#include "config.h"

QNetworkRequest NetworkManager::getRequest(QString url) {
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("Accept", "application/json");

    if(!token.isEmpty()) request.setRawHeader("Authorization", ("Token " + token).toUtf8());
    return request;
}

void NetworkManager::signup(QString name, QString email, QString pass1, QString pass2, std::function<void(QJsonDocument&)> func) {
    QString url = config::QUERY_STRING + "/rest-auth/registration/";
    QNetworkRequest request = getRequest(url);

    QJsonObject json;
    json.insert("username", name);
    json.insert("email", email);
    json.insert("password1", pass1);
    json.insert("password2", pass2);

    QJsonDocument jsonDoc(json);
    QByteArray jsonData = jsonDoc.toJson();

    QNetworkReply* reply = post(request, jsonData);
    QObject::connect(reply, &QNetworkReply::finished, [=](){
        QByteArray responseData = reply->readAll();
        QJsonDocument json = QJsonDocument::fromJson(responseData);
        if(!json["key"].toString().isEmpty()) token = json["key"].toString();
        func(json);
        reply->deleteLater();
    });
}

void NetworkManager::login(QString name, QString email, QString pass, std::function<void(QJsonDocument&)> func) {
    QString url = config::QUERY_STRING + "/rest-auth/login/";
    QNetworkRequest request = getRequest(url);

    QJsonObject json;
    json.insert("username", name);
    json.insert("email", email);
    json.insert("password", pass);

    QJsonDocument jsonDoc(json);
    QByteArray jsonData = jsonDoc.toJson();

    QNetworkReply* reply = post(request, jsonData);
    QObject::connect(reply, &QNetworkReply::finished, [=](){
        QByteArray responseData = reply->readAll();
        QJsonDocument json = QJsonDocument::fromJson(responseData);
        if(!json["key"].toString().isEmpty()) token = json["key"].toString();
        func(json);
        reply->deleteLater();
    });
}

void NetworkManager::logout(void func(QNetworkReply* reply)) {
    QString url = config::QUERY_STRING + "/rest-auth/logout/";
    QNetworkRequest request = getRequest(url);

    QJsonObject json;
    QJsonDocument jsonDoc(json);
    QByteArray jsonData = jsonDoc.toJson();

    QNetworkReply* reply = post(request, jsonData);
    QObject::connect(reply, &QNetworkReply::finished, [=](){
        func(reply);
        token = "";
        reply->deleteLater();
    });
}
void NetworkManager::sendGet(QString url, std::function<void(QNetworkReply*)> func) {
    QNetworkRequest request = getRequest(url);

    QNetworkReply* reply = get(request);
    QObject::connect(reply, &QNetworkReply::finished, [=](){
        func(reply);
    });
}

void NetworkManager::sendPost(QString url, QJsonDocument& body, std::function<void(QNetworkReply*)> func) {
    QNetworkRequest request = getRequest(url);

    QNetworkReply* reply = post(request, body.toJson());
    QObject::connect(reply, &QNetworkReply::finished, [=](){           
        func(reply);
    });
}

void NetworkManager::sendPut(QString url, QJsonDocument& body, std::function<void(QNetworkReply*)> func) {
    QNetworkRequest request = getRequest(url);

    QNetworkReply* reply = put(request, body.toJson());
    QObject::connect(reply, &QNetworkReply::finished, [=](){
        func(reply);
    });
}

void NetworkManager::sendDelete(QString url, std::function<void(QNetworkReply*)> func) {
    QNetworkRequest request = getRequest(url);

    QNetworkReply* reply = deleteResource(request);
    QObject::connect(reply, &QNetworkReply::finished, [=](){
        func(reply);
    });
}


