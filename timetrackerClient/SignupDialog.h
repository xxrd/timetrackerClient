#ifndef SIGNUPDIALOG_H
#define SIGNUPDIALOG_H

#include "NetworkManager.h"
#include <QtWidgets>

class SignupDialog : public QWidget
{
    Q_OBJECT
private:

public:
    SignupDialog(NetworkManager* networkManager, QWidget* pwgt = 0);
signals:
    void signupSuccess();
};
#endif // SIGNUPDIALOG_H
