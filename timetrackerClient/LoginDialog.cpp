#include "LoginDialog.h"

LoginDialog::LoginDialog(NetworkManager* networkManager, QWidget* pwgt) : QWidget(pwgt) {

    auto *layoutMain = new QVBoxLayout(this);
    auto *groupAdd = new QGroupBox(tr("Login"), this);
    auto *loginForm = new QGridLayout(groupAdd);
    loginForm->setVerticalSpacing(10);
    loginForm->setRowStretch(0,1);

    auto *usernameEdit = new QLineEdit(this);
    auto *emailEdit = new QLineEdit(this);
    auto *passwordEdit = new QLineEdit(this);
    passwordEdit->setEchoMode(QLineEdit::Password);

    auto *groupFooter = new QGroupBox(this);
    auto *layoutFooter = new QHBoxLayout(groupFooter);
    auto *errorMessage = new QLabel();
    errorMessage->setStyleSheet("QLabel {font-weight: bold; }");
    layoutFooter->addWidget(errorMessage);

    auto *usernameLabel = new QLabel("Username: ");
    auto *emailLabel = new QLabel("Email: ");
    auto *passwordLabel = new QLabel("Password: ");

    auto *loginButton = new QPushButton("&login");
    auto *signupButton = new QPushButton(tr("signup"), this);

    usernameEdit->setPlaceholderText(tr("username"));
    emailEdit->setPlaceholderText(tr("email"));
    passwordEdit->setPlaceholderText(tr("password"));


    loginForm->addWidget(usernameLabel,0,0);
    loginForm->addWidget(emailLabel,1,0);
    loginForm->addWidget(passwordLabel,2,0);

    loginForm->addWidget(usernameEdit,0,1);
    loginForm->addWidget(emailEdit,1,1);
    loginForm->addWidget(passwordEdit,2,1);

    loginForm->addWidget(loginButton,3,1,Qt::AlignRight);
    loginForm->addWidget(signupButton,4,1,Qt::AlignBottom | Qt::AlignRight);


    layoutMain->addWidget(groupAdd);
    layoutMain->addWidget(groupFooter,0,0);

    resize(840, 480);

    connect(loginButton, &QPushButton::clicked, [=]() {

        networkManager->login(usernameEdit->text(), emailEdit->text(), passwordEdit->text(), [=](QJsonDocument& jsonDocument) {
            errorMessage->setText("");

            if(!jsonDocument["key"].toString().isEmpty()) {
                emit loginSuccess();
                close();
            }
            if(!jsonDocument["username"][0].toString().isEmpty()) {
                errorMessage->setText(errorMessage->text() + "username: " + jsonDocument["username"][0].toString() + "\n");
            }
            if(!jsonDocument["email"][0].toString().isEmpty()) {
                errorMessage->setText(errorMessage->text() + "email: " + jsonDocument["email"][0].toString() + "\n");
            }
            if(!jsonDocument["password"][0].toString().isEmpty()) {
                errorMessage->setText(errorMessage->text() + "password: " + jsonDocument["password"][0].toString() + "\n");
            }
            if(!jsonDocument["non_field_errors"][0].toString().isEmpty()) {
                errorMessage->setText(errorMessage->text() + jsonDocument["non_field_errors"][0].toString() + "\n");
            }

        });

    });

    connect(signupButton, &QPushButton::clicked, [this]() {
        emit signup();
        close();
    });

}
