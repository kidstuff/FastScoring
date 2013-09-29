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
#include <QFileDialog>
#include <QDate>
#include <stdio.h>
#include <stdlib.h>
#include <qrencode.h>
#include "QPrintPreviewDialog"
#include "QPrintPreviewWidget"
#include "globalsetting.h"
#include "QGraphicsView"

FormPrinter::FormPrinter(vector<int> steps)
{
    odd_steps=steps;
    printer=new QPrinter(QPrinter::HighResolution);
    printer->setPageSize(QPrinter::A4);
    printer->setPageMargins(8,18,2,2,QPrinter::Unit());
    QString filename=QFileDialog::getSaveFileName(0,"Save File","print",".pdf");
    printer->setOutputFileName(filename);
    painter=new QPainter(printer);
    n=99;
    h1=307.5;
    h2=302.5;
    text_height=200;
}
void FormPrinter::Print(CourseInfo *r)
{
    painter->begin(printer);
    QPoint p(0,0);
    QPoint p1(0,10604);
    QPoint pr1(5165,1825);
    QPoint pr2(5165,10207);
    QPoint qrcode(5165+29,1825+29);
    this->print_qrcode(qrcode);
    this->print_rectangle(pr1);
    this->print_rectangle(pr2);
    this->print_header(r,p);
    this->print_footer(r,p1);
    this->print_table(r,99);
    painter->end();

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
    painter->setFont(QFont("times new roman",12,1,false));
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
    painter->setFont(QFont("times new roman",12,1,false));
    //School year and current term
    painter->drawText(p.x()+3000,p.y()+1000,r->term+" - "+r->year);
    //Subject name
    painter->drawText(p.x(),p.y()+1200,r->subject_name);
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
void FormPrinter::print_footer(CourseInfo *r, QPoint p)
{
    painter->setPen(QPen(Qt::black,10, Qt::SolidLine, Qt::RoundCap));
    painter->setFont(QFont("times new roman",12,1,false));
    painter->drawRect(-50,p.y(),9250,2000);
    painter->drawText(6000,p.y()+300,r->rpft_day);
    painter->drawText(6350,p.y()+600,r->teach);
    painter->drawText(6350,p.y()+900,r->sign);
    painter->drawText(650,p.y()+300,r->auth);
    painter->drawText(580,p.y()+600,r->sign);
}
void FormPrinter::print_table(CourseInfo* r,int m)
{
    QPoint p_rect1(5165,1825);
    QPoint p_rect2(5165,10207);
    QPoint p_head(0,0);
    QPoint p_foot(0,10604);
    QPoint p_num(0,2222);
    QPoint p_id(400,2222);
    QPoint p_name(1600,2222);
    QPoint p_birth(3800,2222);
    QPoint p_mark(4800,2222);
    QPoint p_smark(5450,2222);
    QPoint p_st(6650,2222);
    QPoint p_sig(7050,2222);
    QPoint p_sbd(8150,2222);


    painter->setFont(QFont("times new roman",12,QFont::Bold));
    painter->setPen(QPen(Qt::black,5, Qt::SolidLine, Qt::RoundCap));
    //stt
    painter->drawRect(p_num.x(),p_num.y(),400,h1);
    painter->drawText(p_num.x(),p_num.y()+text_height,r->tb_stt);
    //mahs
    painter->drawRect(p_id.x(),p_id.y(),1200,h1);
    painter->drawText(p_id.x()+250,p_id.y()+text_height,r->tb_mahs);
    //hoten
    painter->drawRect(p_name.x(),p_name.y(),2200,h1);
    painter->drawText(p_name.x()+700,p_name.y()+text_height,r->tb_hoten);
    //birth
    painter->drawRect(p_birth.x(),p_birth.y(),1000,h1);
    painter->drawText(p_birth.x()+50,p_birth.y()+text_height,r->tb_ngsinh);
    //diem
    painter->drawRect(p_mark.x(),p_mark.y(),650,h1);
    painter->drawText(p_mark.x()+100,p_mark.y()+text_height,r->tb_diem);
    //diemchu
    painter->drawRect(p_smark.x(),p_smark.y(),1200,h1);
    painter->drawText(p_smark.x()+250,p_smark.y()+text_height,r->tb_diemchu);
    //st
    painter->drawRect(p_st.x(),p_st.y(),400,h1);
    painter->drawText(p_st.x()+100,p_st.y()+text_height,r->tb_st);
    //chuki
    painter->drawRect(p_sig.x(),p_sig.y(),1100,h1);
    painter->drawText(p_sig.x()+200,p_sig.y()+text_height,r->tb_chuky);
    //sbd
    painter->drawRect(p_sbd.x(),p_sbd.y(),1000,h1);
    painter->drawText(p_sbd.x()+200,p_sbd.y()+text_height,r->tb_lop);
    //data
    p_num.setY(p_num.y()+h2);
    p_id.setY(p_id.y()+h2);
    p_name.setY(p_name.y()+h2);
    p_birth.setY(p_birth.y()+h2);
    p_mark.setY(p_mark.y()+h2);
    p_smark.setY(p_smark.y()+h2);
    p_st.setY(p_st.y()+h2);
    p_sig.setY(p_sig.y()+h2);
    p_sbd.setY(p_sbd.y()+h2);
    for(int i=0;i<m;i++)
    {
        painter->setFont(QFont("times new roman",12,1,false));

        painter->drawRect(p_num.x(),p_num.y(),400,h1);
        painter->drawText(p_num.x()+40,p_num.y()+text_height,QString::number(i+1));

        painter->drawRect(p_id.x(),p_id.y(),1200,h1);
        painter->drawText(p_id.x()+50,p_id.y()+text_height,r->students[i].student_id);

        painter->drawRect(p_name.x(),p_name.y(),2200,h1);
        painter->drawText(p_name.x()+50,p_name.y()+text_height,r->students[i].last_name
                                                       +" "+r->students[i].middle_name
                                                       +" "+r->students[i].first_name);

        painter->drawRect(p_birth.x(),p_birth.y(),1000,h1);
        painter->drawText(p_birth.x()+50,p_birth.y()+text_height,r->students[i].dayofbirth);

        painter->drawRect(p_mark.x(),p_mark.y(),650,h1);
        QPoint p_point(p_mark.x(),p_mark.y());
        this->print_p_point(QPoint(p_point.x()+90,p_point.y()));

        this->print_p_point(QPoint(p_point.x()+170,p_point.y()));

        this->print_p_point(QPoint(p_point.x()+220,p_point.y()));

        this->print_p_point(QPoint(p_point.x()+300,p_point.y()));

        painter->drawLine(QPoint(p_point.x()+390+50,p_point.y()),QPoint(p_point.x()+390+50,p_point.y()+h2));

        this->print_p_point(QPoint(p_point.x()+480,p_point.y()));

        this->print_p_point(QPoint(p_point.x()+560,p_point.y()));


        painter->drawRect(p_smark.x(),p_smark.y(),1200,h1);

        painter->drawRect(p_st.x(),p_st.y(),400,h1);

        painter->drawRect(p_sig.x(),p_sig.y(),1100,h1);

        painter->drawRect(p_sbd.x(),p_sbd.y(),1000,h1);

        if((i+1)%25==0){
        printer->newPage();
        this->print_rectangle(p_rect1);
        this->print_rectangle(p_rect2);
        this->print_header(r,p_head);
        this->print_footer(r,p_foot);        

        p_num.setY(0);
        p_id.setY(400);
        p_name.setY(1600);
        p_birth.setY(3800);
        p_mark.setY(4800);
        p_smark.setY(5450);
        p_st.setY(6650);
        p_sig.setY(7050);
        p_sbd.setY(8150);

        p_num.setY(2222);
        p_id.setY(2222);
        p_name.setY(2222);
        p_birth.setY(2222);
        p_mark.setY(2222);
        p_smark.setY(2222);
        p_st.setY(2222);
        p_sig.setY(2222);
        p_sbd.setY(2222);
        painter->setFont(QFont("times new roman",12,QFont::Bold));
        painter->setPen(QPen(Qt::black,5, Qt::SolidLine, Qt::RoundCap));
        //stt
        painter->drawRect(p_num.x(),p_num.y(),400,h1);
        painter->drawText(p_num.x(),p_num.y()+text_height,r->tb_stt);
        //mahs
        painter->drawRect(p_id.x(),p_id.y(),1200,h1);
        painter->drawText(p_id.x()+250,p_id.y()+text_height,r->tb_mahs);
        //hoten
        painter->drawRect(p_name.x(),p_name.y(),2200,h1);
        painter->drawText(p_name.x()+700,p_name.y()+text_height,r->tb_hoten);
        //birth
        painter->drawRect(p_birth.x(),p_birth.y(),1000,h1);
        painter->drawText(p_birth.x()+50,p_birth.y()+text_height,r->tb_ngsinh);
        //diem
        painter->drawRect(p_mark.x(),p_mark.y(),650,h1);
        painter->drawText(p_mark.x()+100,p_mark.y()+text_height,r->tb_diem);
        //diemchu
        painter->drawRect(p_smark.x(),p_smark.y(),1200,h1);
        painter->drawText(p_smark.x()+250,p_smark.y()+text_height,r->tb_diemchu);
        //st
        painter->drawRect(p_st.x(),p_st.y(),400,h1);
        painter->drawText(p_st.x()+100,p_st.y()+text_height,r->tb_st);
        //chuki
        painter->drawRect(p_sig.x(),p_sig.y(),1100,h1);
        painter->drawText(p_sig.x()+200,p_sig.y()+text_height,r->tb_chuky);
        //sbd
        painter->drawRect(p_sbd.x(),p_sbd.y(),1000,h1);
        painter->drawText(p_sbd.x()+200,p_sbd.y()+text_height,r->tb_lop);
        }

        p_num.setY(p_num.y()+h2);
        p_id.setY(p_id.y()+h2);
        p_name.setY(p_name.y()+h2);
        p_birth.setY(p_birth.y()+h2);
        p_mark.setY(p_mark.y()+h2);
        p_smark.setY(p_smark.y()+h2);
        p_st.setY(p_st.y()+h2);
        p_sig.setY(p_sig.y()+h2);
        p_sbd.setY(p_sbd.y()+h2);
    }

}
void FormPrinter::print_rectangle(QPoint p)
{
    QPen pen;
    pen.setWidth(30);
    painter->setPen(pen);

    painter->drawLine(p.x(),p.y(),p.x()+270,p.y());
    painter->drawLine(p.x()+270,p.y(),p.x()+270,p.y()+270);
    painter->drawLine(p.x()+270,p.y()+270,p.x(),p.y()+270);
    painter->drawLine(p.x(),p.y()+270,p.x(),p.y());    
}
void FormPrinter::print_p_point(QPoint p)
{
    painter->drawText(p.x(),p.y()+71,".");
    painter->drawText(p.x(),p.y()+146,".");
    painter->drawText(p.x(),p.y()+221,".");
}
void FormPrinter::print_qrcode(QPoint p)
{
    painter->drawRect(p.x(),p.y(),212,212);
    QPen pen;
    pen.setWidth(2);
    QRcode *result;
    QRinput *input = QRinput_new2(1, QR_ECLEVEL_H);
    unsigned char *data = new unsigned char[17];
    for(int i = 0; i < 17; i++) {
        data[i] = '1';
    }
    QPoint pw(p.x()+2,p.y()+2);
    QRinput_append(input, QR_MODE_NUM, 17, data);

    result = QRcode_encodeInput(input);

    int idx = 0;
    for(int i = 0; i < result->width; i++) {
        for(int j = 0; j < result->width; j++) {
            if(result->data[idx] & 1) {
                painter->setPen(QPen(Qt::black,2, Qt::SolidLine, Qt::RoundCap));
                painter->setBrush(Qt::black);
                painter->drawRect(pw.x(),pw.y(),8,8);            
            }
            pw.setX(pw.x()+10);
            idx++;                       
        }
        pw.setX(p.x()+2);
        pw.setY(pw.y()+10);
    }
    painter->setPen(QPen(Qt::black,5, Qt::SolidLine, Qt::RoundCap));
    painter->setBrush(Qt::NoBrush);
    QRcode_free(result);

}
