#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QPainter>
#include "../M1Kryptographie/nbild.h"
#include <QMessageBox>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();
    void paintEvent(QPaintEvent *);
    void draw_image(QPaintEvent *, NBild image);
    QMessageBox messageBox;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::Form *ui;

   int img_width = 400;
   int img_height = 400;

   NBild image = NBild(10,10);
   bool toogle_draw = true;
};

#endif // FORM_H
