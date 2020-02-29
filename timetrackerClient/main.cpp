#include "LoginDialog.h"
#include "MainWindow.h"
#include "NetworkManager.h"
#include "SignupDialog.h"
#include "LoggingCategories.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    NetworkManager* networkManager = new NetworkManager();

    LoginDialog loginDialog(networkManager);
    SignupDialog signupDialog(networkManager);
    MainWindow window;
    loginDialog.show();

    qInstallMessageHandler([](QtMsgType type, const QMessageLogContext &context, const QString &msg) {

        QScopedPointer<QFile>   m_logFile;
        m_logFile.reset(new QFile("./logFile.txt"));
        m_logFile.data()->open(QFile::Append | QFile::Text);
        QTextStream out(m_logFile.data());
        out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ");

        switch (type)
        {
        case QtInfoMsg:     out << "INF "; break;
        case QtDebugMsg:    out << "DBG "; break;
        case QtWarningMsg:  out << "WRN "; break;
        case QtCriticalMsg: out << "CRT "; break;
        case QtFatalMsg:    out << "FTL "; break;
        }

        out << context.category << ": "
            << msg << endl;
        out.flush();
    });

    QObject::connect(&loginDialog, &LoginDialog::signup, [&signupDialog]() {
        signupDialog.show();
    });

    QObject::connect(&loginDialog, &LoginDialog::loginSuccess, [networkManager,&window]() {
        window.setup(networkManager);
        window.show();
    });
    QObject::connect(&signupDialog, &SignupDialog::signupSuccess, [networkManager,&window]() {
        window.setup(networkManager);
        window.show();
    });

    return a.exec();
}
