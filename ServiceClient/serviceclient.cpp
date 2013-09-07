/****************************************************************************
**FastScoring is a program developed entirely based on open source that help
**school staff entering points faster and easieinfo->
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

#include "courseinfo.h"
#include "serviceclient.h"
#include <QDate>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

ServiceClient::ServiceClient()
{
}

void ServiceClient::Login(QString username, QString password){
    Response r;
    emit LoginFinished(r);
}
void ServiceClient::Logout(){
    Response r;
    emit LogoutFinished(r);
}

void ServiceClient::GetCourseInfo(QString idStr){
    CourseInfo* info = new CourseInfo();

    for(int i=0;i<65;i++){
        Student s;
        s.student_id="K36.104.052";
        s.first_name="Đông";
        s.middle_name="Phi";
        s.last_name="Nguyễn";
        s.dayofbirth="14/11/1992";
        s.classname="";
        info->students.append(s);
    }
    info->subject_name="Môn học: Cơ sở dữ liệu";
    info->subject_id="Mã môn học: 1011";
    //header
    info->school_name="TRƯỜNG ĐẠI HỌC SƯ PHẠM TP HCM";
    info->room_name="PHÒNG ĐÀO TẠO";
    info->rp_id="Mẫu in: REP-0001";
    info->rp_day="Ngày in: "+QDate::currentDate().toString();
    info->rp_title="DANH SÁCH GHI ĐIỂM QUÁ TRÌNH";
    info->term="Học kỳ: 2";
    info->year="Năm  học: 2012-2013";
    info->credits="Số tín chỉ: 3";
    info->teacher="Lê Đức Long";
    info->percent="Phần trăm quá trình: 50%";
    info->description="Hình thức đánh giá: Thi viết 120 phút";
    info->exam_day="Ngày thi 01/04/2013";
    info->exam_room="Phòng thi: C307 ADV";
    //table header
    info->tb_stt="STT";
    info->tb_mahs="Mã HS";
    info->tb_hoten="Họ và Tên";
    info->tb_ngsinh="Ngày sinh";
    info->tb_diem="Điểm";
    info->tb_diemchu="Điểm chữ";
    info->tb_st="ST";
    info->tb_chuky="Chữ ký";
    info->tb_lop="Số BD";
    //left footer
    info->auth="Giáo vụ xác nhận";
    info->sign="(Ký và ghi rõ họ tên)";
    //right footer
    info->rpft_day="Tp HCM, Ngày     Tháng    Năm";
    info->teach="Giảng viên giảng dạy";

    Response r;
    emit GetCourseInfoFinished(info, r);
}

void ServiceClient::GetCourseList(QString year, QString term, QString faculty,
                   QString supject, QString lecturer, QUrlQuery* extra){

    QNetworkAccessManager* manager = new QNetworkAccessManager();
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(cLstReplRead(QNetworkReply*)));
    manager->get(QNetworkRequest(QUrl("http://localhost:12345/GetCourseList")));
    //manager->deleteLater();
}

void ServiceClient::SubmitScores(){

}

void ServiceClient::cLstReplRead(QNetworkReply* repl) {
    QJsonDocument json = QJsonDocument::fromJson(repl->readAll());
    repl->deleteLater();
    sender()->deleteLater();

    Response r;
    CourseSummaryList* summaries = new CourseSummaryList();
    if(!json.isArray()) {
        r.Status = 500;
        emit GetCourseListFinished(summaries, r);
        return;
    }
    QJsonArray jArrCLst = json.array();
    QJsonValue val, field;
    QJsonObject obj;
    for(int i=0; i < jArrCLst.size(); i++) {
        val = jArrCLst[i];
        if(!val.isObject()) {
            continue;
        }
        obj = val.toObject();
        CourseSummary summary;
        field = obj.value("course_id");
        if(!field.isUndefined()) {
            summary.course_id = field.toString();
        }

        field = obj.value("credits");
        if(!field.isUndefined()) {
            summary.credits = field.toString();
        }

        field = obj.value("description");
        if(!field.isUndefined()) {
            summary.description = field.toString();
        }

        field = obj.value("percent");
        if(!field.isUndefined()) {
            summary.percent = field.toString();
        }

        field = obj.value("subject");
        if(!field.isUndefined()) {
            summary.subject = field.toString();
        }

        field = obj.value("term");
        if(!field.isUndefined()) {
            summary.term = field.toString();
        }

        field = obj.value("year");
        if(!field.isUndefined()) {
            summary.year = field.toString();
        }

        field = obj.value("lecturer");
        if(!field.isUndefined()) {
            summary.lecturer = field.toString();
        }
        summaries->append(summary);
    }


//    for(int i=0; i<30;i++){
//        CourseSummary summary;
//        summary.course_id = "1231231231";
//        summary.credits = "2";
//        summary.description = "qwejkwhqe 12312";
//        summary.percent = "20";
//        summary.subject = "tin hoc dai cuong";
//        summary.term = "2";
//        summary.year = "2013";
//        summary.lecturer ="ng v a";
//        summaries->append(summary);
//    }

    emit GetCourseListFinished(summaries, r);
}
