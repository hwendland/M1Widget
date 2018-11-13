#include <iostream>
#include "form.h"
#include "ui_form.h"

#include <QPainter>
#include "../M1Kryptographie/nbild.h"
#include "../M1Kryptographie/cbild.h"

#include <QFile>
#include <QFileDialog>
#include <string>

#include <QMessageBox>

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
        this->draw_image(e,image);
}

void Form::draw_image(QPaintEvent *, NBild image){ //draw
    int nrows = static_cast<int>(image.nrows);
    int ncols = static_cast<int>(image.ncols);

    QPainter painter(this);
    painter.setBrush(Qt::black);

    for (int row = 0; row < nrows; row++){
        for (int col = 0; col < ncols; col++){
            if(image(static_cast<size_t>(row), static_cast<size_t>(col)) == 0){
                painter.setBrush(Qt::black);
                painter.setPen(Qt::black);
            } else {
                painter.setBrush(Qt::white);
                painter.setPen(Qt::white);
            }
            int x1 = (col*img_width)/ncols;
            int y1 = (row*img_height)/nrows;
            int x2 = ((col+1)*img_width)/ncols;
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
    try{
        image.import(directory);
    } catch(int e){
        if(e == 1){
            messageBox.critical(nullptr,"Error","Can't find the requested file");
        } else if (e == 0){
            messageBox.critical(nullptr,"Error","Invalid input format");
        }
    }
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
    try{
        overlay_img.import(directory);
    } catch(int e){
        if(e == 1){
            messageBox.critical(nullptr,"Error","Can't find the requested file");
        } else if (e == 0){
            messageBox.critical(nullptr,"Error","Invalid input format");
        }
    }
    string key;
    if(ui->radioButton->isChecked()){
        key = "A";
    } else {
        key = "B";
    }

    if (overlay_img.ncols == image.ncols && overlay_img.nrows == image.nrows){
        CBild crypt = CBild(key);
        image = crypt.overlay(image,overlay_img);
    } else {
        messageBox.critical(nullptr,"Error","Incompatible image sizes");
    }

    toogle_draw = true;
    update();
}

void Form::on_pushButton_5_clicked() //save
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as");
    string directory =  fileName.toUtf8().constData();

    try{
        image.writeToFile(directory);
    } catch(int e){
        if(e == 1){
            messageBox.critical(nullptr,"Error","Can't find the requested file");
        }
    }
    toogle_draw = true;
    update();
}


