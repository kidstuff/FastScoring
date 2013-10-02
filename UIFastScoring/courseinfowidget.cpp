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

#include "formprinter.h"
#include "courseinfowidget.h"
#include "globalsetting.h"
#include "ui_courseinfowidget.h"
#include "mainwindow.h"
#include <QDebug>
#include <QDate>
#include <QPrintPreviewWidget>
#include <QPrinter>

CourseInfoWidget::CourseInfoWidget(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::CourseInfoWidget)
{
    QPrinter *printer=new QPrinter(QPrinter::HighResolution);
    fprinter=new FormPrinter(printer);

    ui->setupUi(this);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    connect(this, &CourseInfoWidget::PrintClicked,
            fprinter, &FormPrinter::Print);
    connect(ui->btPrint, &QPushButton::clicked,
            this, &CourseInfoWidget::Print);
}

void CourseInfoWidget::LoadCourseList() {
    emit GetCourseList("2013", "2", "id-f-123", "id-s-456", "id-l-789", NULL);
}

void CourseInfoWidget::DisplayCourseList(CourseSummaryList *sumary, Response r) {
    ui->tableView->setModel(sumary);
}

CourseInfoWidget::~CourseInfoWidget()
{
    delete ui;
}

void CourseInfoWidget::Print() {
    CourseInfo* r = new CourseInfo();

    for(int i=0;i<75;i++){
        Student s;
        s.student_id="K36.104.052";
        s.first_name="Đông";
        s.middle_name="Phi";
        s.last_name="Nguyễn";
        s.dayofbirth="14/11/1992";
        s.classname="";
        r->students.append(s);
    }

    r->subject_name="Môn học: Cơ sở dữ liệu";
    r->subject_id="Mã môn học: 1011";
    //header
    r->school_name="TRƯỜNG ĐẠI HỌC SƯ PHẠM TP HCM";
    r->room_name="PHÒNG ĐÀO TẠO";
    r->rp_id="Mẫu in: REP-0001";
    r->rp_day="Ngày in: "+QDate::currentDate().toString();
    r->rp_title="DANH SÁCH GHI ĐIỂM QUÁ TRÌNH";
    r->term="Học kỳ: 2";
    r->year="Năm  học: 2012-2013";
    r->credits="Số tín chỉ: 3";
    r->teacher="Lê Đức Long";
    r->percent="Phần trăm quá trình: 50%";
    r->description="Hình thức đánh giá: Thi viết 120 phút";
    r->exam_day="Ngày thi 01/04/2013";
    r->exam_room="Phòng thi: C307 ADV";
    //table header
    r->tb_stt="STT";
    r->tb_mahs="Mã HS";
    r->tb_hoten="Họ và Tên";
    r->tb_ngsinh="Ngày sinh";
    r->tb_diem="Điểm";
    r->tb_diemchu="Điểm chữ";
    r->tb_st="ST";
    r->tb_chuky="Chữ ký";
    r->tb_lop="Số BD";
    //left footer
    r->auth="Giáo vụ xác nhận";
    r->sign="(Ký và ghi rõ họ tên)";
    //right footer
    r->rpft_day="Tp HCM, Ngày     Tháng    Năm";
    r->teach="Giảng viên giảng dạy";
    emit PrintClicked(r);
}
