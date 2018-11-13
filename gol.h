#ifndef GOL_H
#define GOL_H

#include <QWidget>
#include "../M1CellularAutomaton/gameoflife.h"
#include <QtCore>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class GOL;
}

class GOL : public QWidget
{
    Q_OBJECT

public:
    explicit GOL(QWidget *parent = nullptr);
    ~GOL();
    void paintEvent(QPaintEvent *e);
    void draw_board(QPaintEvent *);
    GameOfLife game = GameOfLife();
    void mousePressEvent( QMouseEvent*ev);
    QMessageBox messageBox;

    QTimer *timer;

public slots:
    void MySlot();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_spinBox_valueChanged(int arg1);

private:
    Ui::GOL *ui;
    int img_width = 400;
    int img_height = 400;
};

#endif // GOL_H
