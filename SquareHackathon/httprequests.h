#ifndef HTTPREQUESTS_H
#define HTTPREQUESTS_H

#include <QJsonObject>
#include <QJsonDocument>


class HttpRequests
{
public:
    HttpRequests();
    QByteArray apiCode;
    void addTeamMember(QJsonObject json);
    QJsonObject getTeamMembers();
    void inactivateTeamMember(QString teamMemberID);


private:
    QByteArray getAPICode();
};

#endif // HTTPREQUESTS_H
