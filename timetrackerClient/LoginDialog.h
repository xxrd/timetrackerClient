#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include "NetworkManager.h"
#include <QtWidgets>
#include <QDebug>

class LoginDialog : public QWidget {
    Q_OBJECT
private:

public:
    LoginDialog(NetworkManager* networkManager, QWidget* pwgt = 0);
signals:
    void loginSuccess();
    void signup();
};
#endif // LOGINDIALOG_H
