/****************************************************************************
**FastScoring is a program developed entirely based on open source that help
**school staff entering points faster and easier.
**    Copyright (C) 2013  OPEN-VN.ORG Team
**
**    This program is free software: you can redistribute it and/or modify
**    it under the terms of the GNU Affero General Public License as published by
**    the Free Software Foundation, either version 3 of the License, or
**    (at your option) any later version.
**
**    This program is distributed in the hope that it will be useful,
**    but WITHOUT ANY WARRANTY; without even the implied warranty of
**    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**    GNU Affero General Public License for more details.
**
**    You should have received a copy of the GNU Affero General Public License
**    along with this program.  If not, see <http://www.gnu.org/licenses/>.
****************************************************************************/

#ifndef SERVICECLIENT_H
#define SERVICECLIENT_H

#include "response.h"
#include "coursesummary.h"
#include <QString>
#include <QUrlQuery>
#include <QAbstractTableModel>

class CourseInfo;
class QNetworkReply;

class ServiceClient : public QObject
{
    Q_OBJECT
public:
    ServiceClient();
private:
    QByteArray token;
public slots:
    void Login(QString username, QString password);
    void Logout();
    void GetCourseInfo(QString idStr);
    void GetCourseList(QString year, QString term, QString faculty,
                       QString supject, QString lecturer, QUrlQuery* extra);
    void SubmitScores();
signals:
    void LoginFinished(Response r);
    void LogoutFinished(Response r);
    void GetCourseInfoFinished(CourseInfo* inf, Response r);
    void GetCourseListFinished(CourseSummaryList* sumary, Response r);

private slots:
    void cLstReplRead(QNetworkReply* repl);
    void loginReplRead(QNetworkReply* repl);
};

#endif // SERVICECLIENT_H
