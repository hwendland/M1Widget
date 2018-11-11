#include "widget.h"
#include "ui_widget.h"
#include "form.h"
#include "gol.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->tabWidget->insertTab(0,new Form(), QString("Krypto"));
    ui->tabWidget->insertTab(0,new GOL(), QString("GOL"));

}

Widget::~Widget()
{
    delete ui;
}
