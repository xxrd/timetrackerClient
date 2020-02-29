#ifndef CONFIG_H
#define CONFIG_H

#include <QString>

namespace config {

    const QString HOST = "127.0.0.1";
    const QString PORT = "8000";
    const QString API_VERSION = "1";
    const QString QUERY_STRING = "http://" + HOST + ":" + PORT + "/api/v" + API_VERSION;

}

#endif // CONFIG_H
