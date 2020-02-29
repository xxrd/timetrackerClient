#include "SignupDialog.h"

SignupDialog::SignupDialog(NetworkManager* networkManager, QWidget* pwgt) : QWidget(pwgt) {

    auto *layoutMain = new QVBoxLayout(this);
    auto *groupAdd = new QGroupBox(tr("Signup"), this);
    auto *loginForm = new QGridLayout(groupAdd);
    loginForm->setVerticalSpacing(10);
    loginForm->setRowStretch(0,1);

    auto *usernameEdit = new QLineEdit(this);
    auto *emailEdit = new QLineEdit(this);
    auto *passwordEdit = new QLineEdit(this);
    auto *confirmPasswordEdit = new QLineEdit(this);
    passwordEdit->setEchoMode(QLineEdit::Password);
    confirmPasswordEdit->setEchoMode(QLineEdit::Password);

    auto *groupFooter = new QGroupBox(this);
    auto *layoutFooter = new QHBoxLayout(groupFooter);
    auto *errorMessage = new QLabel();
    errorMessage->setStyleSheet("QLabel {font-weight: bold; }");
    layoutFooter->addWidget(errorMessage);

    auto *usernameLabel = new QLabel("Username: ");
    auto *emailLabel = new QLabel("Email: ");
    auto *passwordLabel = new QLabel("Password: ");
    auto *confirmPasswordLabel = new QLabel("Confirm password: ");

    auto *signupButton = new QPushButton("&signup");

    usernameEdit->setPlaceholderText(tr("username"));
    emailEdit->setPlaceholderText(tr("email"));
    passwordEdit->setPlaceholderText(tr("password"));
    confirmPasswordEdit->setPlaceholderText("confirm password");

    loginForm->addWidget(usernameLabel,0,0);
    loginForm->addWidget(emailLabel,1,0);
    loginForm->addWidget(passwordLabel,2,0);
    loginForm->addWidget(confirmPasswordLabel,3,0);

    loginForm->addWidget(usernameEdit,0,1);
    loginForm->addWidget(emailEdit,1,1);
    loginForm->addWidget(passwordEdit,2,1);
    loginForm->addWidget(confirmPasswordEdit,3,1);

    loginForm->addWidget(signupButton,4,1,Qt::AlignRight | Qt::AlignBottom);

    layoutMain->addWidget(groupAdd);
    layoutMain->addWidget(groupFooter,0,0);

    resize(840, 480);

    connect(signupButton, &QPushButton::clicked, [=]() {

        networkManager->signup(usernameEdit->text(), emailEdit->text(), passwordEdit->text(), confirmPasswordEdit->text(), [=](QJsonDocument& jsonDocument) {
            errorMessage->setText("");

            if(!jsonDocument["key"].toString().isEmpty()) {
                emit signupSuccess();
                close();
            }
            if(!jsonDocument["username"][0].toString().isEmpty()) {
                errorMessage->setText(errorMessage->text() + "username: " + jsonDocument["username"][0].toString() + "\n");
            }
            if(!jsonDocument["email"][0].toString().isEmpty()) {
                errorMessage->setText(errorMessage->text() + "email: " + jsonDocument["email"][0].toString() + "\n");
            }
            if(!jsonDocument["password1"][0].toString().isEmpty()) {
                errorMessage->setText(errorMessage->text() + "password: " + jsonDocument["password1"][0].toString() + "\n");
            }
            if(!jsonDocument["password2"][0].toString().isEmpty()) {
                errorMessage->setText(errorMessage->text() + "confirm password: " + jsonDocument["password2"][0].toString() + "\n");
            }
            if(!jsonDocument["non_field_errors"][0].toString().isEmpty()) {
                errorMessage->setText(errorMessage->text() + jsonDocument["non_field_errors"][0].toString() + "\n");
            }

        });

    });

}
