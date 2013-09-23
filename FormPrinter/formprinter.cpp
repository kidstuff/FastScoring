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
#include "QFileDialog"

FormPrinter::FormPrinter(vector<int> steps)
{
    odd_steps=steps;
    printer=new QPrinter(QPrinter::HighResolution);
    QString filename= QFileDialog(this,"Save File","print",".pdf");
    printer->setOutputFileName(filename);
    printer->setPageSize(QPrinter::A4);
    printer->setPageMargins(8,18,2,2,QPrinter::Unit());
    printer->setOutputFormat(QPrinter::NativeFormat);
    painter = new QPainter();
    n=99;
    h1=307.5;
    h2=302.5;
    text_height=200;
}
void FormPrinter::Print(CourseInfo *r)
{
    QPoint p(0,0);
    this->print_header(r,p);
}
CourseInfo* FormPrinter::generatedata(int n){
    CourseInfo* r=new CourseInfo();

    for(int i=0;i<n;i++){
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
    return r;
}
void FormPrinter::print_header(CourseInfo* r, QPoint p){
    //header height:1955px, width:9250
    //p(0,0)
    QPen pen;
    pen.setWidth(10);
    painter->setPen(pen);
    painter->setFont(QFont("times new roman",12,1,FALSE));
    //Draw a rectanlge contain header
    painter->drawRect(p.x()-50,p.y()-250,9250,1955);
    painter->setPen(QPen(Qt::black,5, Qt::SolidLine, Qt::RoundCap));
    //School name
    painter->drawText(p.x(),p.y(),r->school_name);
    //Department name
    painter->drawText(p.x()+500,p.y()+200,r->room_name);
    //Report ID
    painter->drawText(p.x()+7000,p.y(),r->rp_id);
    //Day print report
    painter->drawText(p.x()+7000,p.y()+200,r->rp_day);
    painter->setFont(QFont("times new roman",12,QFont::Bold));
    //Report name
    painter->drawText(p.x()+2550,p.y()+800,r->rp_title);
    painter->setFont(QFont("times new roman",12,1,FALSE));
    //School year and current term
    painter->drawText(p.x()+3000,p.y()+1000,r->term+" - "+r->year);
    //Subject name
    painter->drawText(p.x(),p.y()+1200,r->subject);
    //Subject credits
    painter->drawText(p.x()+7000,p.y()+1200,r->credits);
    //Subject id
    painter->drawText(p.x(),p.y()+1400,r->subject_id);
    //Percent of mark
    painter->drawText(p.x()+7000,p.y()+1400,r->percent);
    //Exam forms
    painter->drawText(p.x(),p.y()+1600,r->description);
    //Exam day
    painter->drawText(p.x()+4500,p.y()+1600,r->exam_day);
    //Exam room
    painter->drawText(p.x()+7000,p.y()+1600,r->exam_room);
}
