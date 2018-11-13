#include "gol.h"
#include "ui_gol.h"
#include <iostream>

#include <QPainter>
#include <QMouseEvent>
#include <QFileDialog>
#include <QFile>

//#include "../M1CellularAutomaton/gameoflife.h"
//#include "../M1CellularAutomaton/gameoflife.cpp"

GOL::GOL(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GOL)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this,SLOT(MySlot()));
}

GOL::~GOL()
{
    delete ui;
}

void GOL::paintEvent(QPaintEvent *e){
    draw_board(e);
    QPainter painter(this);
}

void GOL::draw_board(QPaintEvent *){
    int ncols = game.ncols;
    int nrows = game.nrows;

    QPainter painter(this);

    for (int row = 0; row < nrows; row++){
        for (int col = 0; col < ncols; col++){
            if(game.currentGeneration[row][col].status == 1){
                painter.setBrush(Qt::black);
            } else {
                painter.setBrush(Qt::white);
            }

            int x1 = (col*img_width)/ncols;
            int y1 = (row*img_height)/nrows;
            int x2 = ((col+1)*img_width)/ncols;
            int y2 = ((row+1)*img_height)/nrows;

            painter.drawRect(x1,y1,
                             x2-x1,y2-y1);
        }
    }
}

void GOL::mousePressEvent(QMouseEvent*ev){
    QPoint point = ev -> pos();

    int xpos =  point.x();
    int ypos =  point.y();

    int ncols = game.ncols;
    int nrows = game.nrows;

    if (xpos >= img_height || ypos >= img_width){
        //throw 0;
    } else {
        int col = (xpos * ncols)/img_width;
        int row = (ypos * nrows)/img_height;

        if (game.currentGeneration[row][col].status == 0){
            game.currentGeneration[row][col] = Cell(row, col, 1);
        } else {
            game.currentGeneration[row][col] = Cell(row, col, 0);
        }
    }
    update();

}

void GOL::MySlot(){
    game.evolve();
    update();
}



void GOL::on_pushButton_clicked()
{
    int intervall = ui->spinBox->value();
    timer -> setInterval(intervall);

    if(timer->isActive()){
        timer->stop();
    } else {
        timer->start(intervall);
    }
}



void GOL::on_pushButton_2_clicked()
{
    int intervall = ui->spinBox->value();
    timer -> setInterval(intervall);
}

void GOL::on_pushButton_3_clicked()
{
    int size = ui->spinBox_2->value();
    pair<int,int> dimensions = {size, size};
    game.change_dimensions(dimensions);
    game.get_random_field();
    update();
}



void GOL::on_pushButton_4_clicked() //save
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as");
    string directory =  fileName.toUtf8().constData();
    if(!(directory == "")){
        game.write_to_file(directory);
    }
    update();
}

void GOL::on_pushButton_5_clicked() //load
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    string directory =  fileName.toUtf8().constData();

    update();
}

void GOL::on_pushButton_6_clicked()
{
    int ncols = game.ncols;
    int nrows = game.nrows;

    for (int row = 0; row < nrows; row++){
        for (int col = 0; col < ncols; col++){
            game.currentGeneration[row][col] = Cell(row, col, 0);
        }
    }

    update();
}

void GOL::on_spinBox_valueChanged(int arg1)
{
    int intervall = ui->spinBox->value();
    timer -> setInterval(intervall);
}

