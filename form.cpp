#include <iostream>
#include "form.h"
#include "ui_form.h"

#include <QPainter>
#include "../M1Kryptographie/nbild.h"
#include "../M1Kryptographie/cbild.h"

#include <QFile>
#include <QFileDialog>
#include <string>

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{

    ui->setupUi(this);
    toogle_draw = false;

}

Form::~Form()
{
    delete ui;
}

void Form::paintEvent(QPaintEvent *e){
    if(toogle_draw == true){
        this->draw_image(e,image);
    }
}

void Form::draw_image(QPaintEvent *, NBild image){ //draw
    int nrows = image.nrows;
    int ncols = image.ncols;

    QPainter painter(this);
    painter.setBrush(Qt::black);


    for (int row = 0; row < nrows; row++){
        for (int col = 0; col < ncols; col++){
            if(image(row, col) == 0){
                painter.setBrush(Qt::black);
                painter.setPen(Qt::black);
            } else {
                painter.setBrush(Qt::white);
                painter.setPen(Qt::white);
            }
            int x1 = (col*img_width)/ncols +10;
            int y1 = (row*img_height)/nrows;
            int x2 = ((col+1)*img_width)/ncols +10;
            int y2 = ((row+1)*img_height)/nrows;

            painter.drawRect(x1,y1,
                             x2-x1,y2-y1);
        }
    }
    toogle_draw = false;
}

void Form::on_pushButton_clicked() //load
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");

    string directory =  fileName.toUtf8().constData();
    image.import(directory);
    toogle_draw = true;
    update();
}



void Form::on_pushButton_2_clicked() //encode
{
    string key;
    if(ui->radioButton->isChecked()){
        key = "A";
    } else {
        key = "B";
    }

    CBild crypt = CBild(key);
    image = crypt.encode(image);
    image.writeToFile("aaaa");

    toogle_draw = true;
    update();
}

void Form::on_pushButton_3_clicked() //decode
{
    string key;
    if(ui->radioButton->isChecked()){
        key = "A";
    } else {
        key = "B";
    }

    CBild crypt = CBild(key);
    image = crypt.decode(image);

    toogle_draw = true;
    update();
}

void Form::on_pushButton_4_clicked() //overlay
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    string directory =  fileName.toUtf8().constData();

    NBild overlay_img;
    overlay_img.import(directory);

    string key;
    if(ui->radioButton->isChecked()){
        key = "A";
    } else {
        key = "B";
    }

    CBild crypt = CBild(key);
    image = crypt.overlay(image,overlay_img);

    toogle_draw = true;
    update();
}



void Form::on_pushButton_5_clicked() //save
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as");
    string directory =  fileName.toUtf8().constData();

    image.writeToFile(directory);

    toogle_draw = true;
    update();

}
